
pipeline {
    agent none
    triggers {
        cron('H 20 * * 1-5') // nightly around 8 pm
        //pollSCM('H/5 * * * *') // check git every five minutes
    }
    parameters {
        string(name: 'BC_LIB', defaultValue: '', description: 'braincloud-unreal-plugin-src branch (blank for .gitmodules)')
        string(name: 'TEST_NAME', defaultValue: 'Authentication', description: 'test filter')
    }
    stages {
            
        stage('Unit Tests on Mac') {
            agent {
                label 'clientUnit'
            }
            environment {
			    PATH = "/Applications/CMake.app/Contents/bin:/usr/local/bin:${env.PATH}"
			    UE_INSTALL_PATH="/Users/Shared/Epic Games/UE_5.1"
                UE_EDITOR_CMD="UnrealEditor-Cmd"
                UE_VERSION="5.1"
                BRANCH_NAME="develop"
  			}
            steps {
                deleteDir()
                checkout([$class: 'GitSCM', branches: [[name: '*/develop']], extensions: [[$class: 'SubmoduleOption', disableSubmodules: false, parentCredentials: false, recursiveSubmodules: true, reference: '', trackingSubmodules: false]], userRemoteConfigs: [[url: 'https://github.com/getbraincloud/braincloud-unreal.git']]])				
			    sh 'autobuild/checkout-submodule.sh ${BC_LIB}'
                sh '~/braincloud-bin/setupunrealtests.sh'
			    sh 'autobuild/runtest.sh ${TEST_NAME}'
            }
            post {
                success {
					fileOperations([fileCopyOperation(excludes: '', flattenFiles: false, includes: '/Users/buildmaster/Library/Logs/Unreal Engine/BCSubsystemServer/RunTests.log', renameFiles: false, sourceCaptureExpression: '', targetLocation: 'Results-Mac', targetNameExpression: ''), fileCopyOperation(excludes: '', flattenFiles: false, includes: 'TestResults/index.json', renameFiles: false, sourceCaptureExpression: '', targetLocation: 'Results-Mac', targetNameExpression: '')])
                    archiveArtifacts artifacts: 'Results-Mac/*.*', followSymlinks: false
                }
            }
        } 
                    
        stage('Unit Tests on Windows') {
            agent {
                label 'unrealWindows'
            }
            environment {
                UE_VERSION="5.1"
			    UE_RUNUAT_PATH="\"D:\\ProgramFiles\\UE_5.1\\Engine\\Build\\BatchFiles\\RunUAT.bat\""
                UE_EDITOR_PATH="\"D:\\ProgramFiles\\UE_5.1\\Engine\\Binaries\\Win64\\UnrealEditor-cmd.exe\""
                BRANCH_NAME="develop"
            }
            steps {
                deleteDir()
                checkout([$class: 'GitSCM', branches: [[name: '*/develop']], extensions: [[$class: 'SubmoduleOption', disableSubmodules: false, parentCredentials: false, recursiveSubmodules: true, reference: '', trackingSubmodules: false]], userRemoteConfigs: [[url: 'https://github.com/getbraincloud/braincloud-unreal.git']]])				
            	bat 'C:\\Users\\buildmaster\\braincloud-bin\\setuptestsunreal.bat'
            	bat 'autobuild\\runtest.bat %TEST_NAME%'
            }
            post {
                success {
                    archiveArtifacts artifacts: 'TestResults/index.json, saved/logs/RunTests.log', followSymlinks: false
                }
            }
        } 
                            
        stage('Unit Tests on Windows UE4') {
            agent {
                label 'unrealWindows'
            }
            environment {
                UE_VERSION="4.27"
			    UE_RUNUAT_PATH="\"D:\\ProgramFiles\\UE_4.27\\Engine\\Build\\BatchFiles\\RunUAT.bat\""
                UE_EDITOR_PATH="\"D:\\ProgramFiles\\UE_4.27\\Engine\\Binaries\\Win64\\UE4Editor-cmd.exe\""
                BRANCH_NAME="ue4-tests"
            }
            steps {
                deleteDir()
                checkout([$class: 'GitSCM', branches: [[name: '*/ue4-tests']], extensions: [[$class: 'SubmoduleOption', disableSubmodules: false, parentCredentials: false, recursiveSubmodules: true, reference: '', trackingSubmodules: false]], userRemoteConfigs: [[url: 'https://github.com/getbraincloud/braincloud-unreal.git']]])				
            	bat 'C:\\Users\\buildmaster\\braincloud-bin\\setuptestsunreal.bat'
            	bat 'autobuild\\runtest.bat %TEST_NAME%'
            }
            post {
                success {
                    archiveArtifacts artifacts: 'TestResults/index.json, saved/logs/RunTests.log', followSymlinks: false
                }
            }
        } 
        // end stages
    }
    // end pipeline
}