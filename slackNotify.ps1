# These templates can be moved to an external file and passed as params
$templateSuccess = '
{
  "attachments": [
    {
      "color": "#36a64f",
      "blocks": [
        {
          "type": "section",
          "text": {
              "text": "Build success: *!%jobName* build (!%buildNumber)",
              "type": "mrkdwn"
          }
        }
      ]
    }
  ]
}'

$templateFailed = '{
  "text": "Build failure: *!%jobName* build (!%buildNumber)",
  "attachments": [
      {
      "color": "#a30000",
      "blocks": [
          {
          "type": "divider"
          },
          {
          "type": "section",
          "text": {
              "text": "!%failedMessage",
              "type": "mrkdwn"
          }
          },
          {
          "type": "divider"
          },
          {
          "type": "section",
          "text": {
              "type": "mrkdwn",
              "text": "View report log on Jenkins."
          },
          "accessory": {
              "type": "button",
              "text": {
              "type": "plain_text",
              "text": "Open",
              "emoji": true
              },
              "value": "view",
              "url": "!%jobUrl",
              "action_id": "button-action"
          }
        }
      ]
    }
  ]
  }'
  
Function BuildMessageJSON([String[]]$arg) {
    For ($i = 0; $i -lt $arg.length; $i++) {
        $returnJSON += $arg[$i]
        $returnJSON += '\r\n'
    }
    return $returnJSON
}

Function ReportToSlack([String]$payload) {
  if(!$payload) {
    Write-Output 'Invalid Report Success Payload.'
    return 1
  }
  
  $token=$buildParams['slackToken']
  Invoke-WebRequest -UseBasicParsing https://hooks.slack.com/services/$token `
  -ContentType "application/json" -Method POST -Body $payload
}

Function ReportSuccess() {
  $buildNumber=$buildParams['buildNumber']
  $jobName=$buildParams['jobName']

  $templatePayload=$templateSuccess -replace '!%jobName', $jobName
  $templatePayload=$templatePayload -replace '!%buildNumber', $buildNumber
  return ReportToSlack($templatePayload)
}
Function ReportFailure([String]$failedMessage) {
  $buildNumber=$buildParams['buildNumber']
  $jobName=$buildParams['jobName']
  $jobURL=$buildParams['jobURL']
  
  $templatePayload=$templateFailed -replace '!%jobName', $jobName
  $templatePayload=$templatePayload -replace '!%buildNumber', $buildNumber
  $templatePayload=$templatePayload -replace '!%failedMessage', $failedMessage
  $templatePayload=$templatePayload -replace '!%jobUrl', $jobUrl
  Write-Output($templatePayload)
  return ReportToSlack($templatePayload)
}

Function GetLogFile() {
  $user = $buildParams['pipelineUsername']
  $pass = $buildParams['pipelinePassword']
  $buildNumber=$buildParams['buildNumber']
  $jobUrl=$buildParams['jobURL']

  $jobUrl=$jobUrl+$buildNumber+'/'+'console'
  $pair = "$($user):$($pass)"
  $encodedCreds = [System.Convert]::ToBase64String([System.Text.Encoding]::ASCII.GetBytes($pair))
  $basicAuthValue = "Basic $encodedCreds"

  $Headers = @{
      Authorization = $basicAuthValue
  }
  Invoke-WebRequest -Uri $jobUrl -OutFile "\testResults" -Headers $Headers
}

Function DumpBuildArgs {
  foreach($key in $buildParams.keys)
  {
      $param = '{0}={1}' -f $key, $buildParams[$key]
      Write-Output $param
  }
}

Function LogErrorToConsole([String]$errorMessage) {
  Write-Output $errorMessage
}

Function DisplayUsage {
  Write-Output 'Usage: notifySlack.ps1 -param:value'
  Write-Output 'Params:
       -slackToken The Slack API notification token -> T0291B812JV/B029H8TUBM3/G6z5K1anq....
       -buildNumber The Jenkins build number
       -jobName The Jenkins job name
       -jobURL The Jenkins job URL
       -pipelineUsername The Jenkins pipeline user name(should be passed using the pipeline credentials plugin)
       -pipelinePassword The Jenkins pipeline password(should be passed using the pipeline credentials plugin)
       -regExp The regexp pattern to match the failed messages
       [-cmakeFailed:true] Optional parameter to indicate a cmake failure
       [-buildFailed:true] Optional parameter to indicate a build failure'
  Write-Output '*Note that any parameter values containing spaces have to be in quote -> -jobName:"Test Job"'
}

Function ValidateArgs() {
  $requiredArgs = @('slackToken','buildNumber','jobName','jobURL','pipelineUsername','pipelinePassword',"regExp")

  foreach($param in $requiredArgs)
  {
    if(!$buildParams[$param]) {
      LogErrorToConsole("Missing argument -$param")
      exit 1
    }
  }
}

Function RunRegexp {
  $input_path = './TestResults/index.json'
  $regex = $buildParams['regExp']
  return select-string -CaseSensitive -Path $input_path -Pattern $regex -AllMatches | % { $_.Matches } | % { $_.Value }
}

  if($args.length -eq 0) {
    DisplayUsage
    exit 1 
  }
  
  # Define and populate the buildParams Hashtable
  $buildParams = @{}

  For ($i = 0; $i -lt $args.length; $i += 2) {
    # Remove the '-' and ':' from the key name
    $args[$i]=$args[$i] -replace '-', ''
    $args[$i]=$args[$i] -replace ':', ''

    $buildParams.Add($args[$i], $args[$i+1])  
  }
  
  ValidateArgs
 
  $TestsDidFail=Select-String -Pattern "^.*Test Failure.*$" './TestResults/index.json' #Finished: FAILURE
  
  $TestsDidFail=RunRegexp

  $NotificationJSON=BuildMessageJSON($TestsDidFail)

  if($NotificationJSON) {
    ReportFailure $NotificationJSON
    exit 1
  } else {
    ReportSuccess
    exit 0
  }