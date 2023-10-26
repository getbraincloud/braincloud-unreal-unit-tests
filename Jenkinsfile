
pipeline {
    agent none
    //triggers {
        //cron('H 20 * * 1-5') // nightly around 8 pm
        //pollSCM('H/5 * * * *') // check git every five minutes
    //}
    parameters {
        string(name: 'TEST_BRANCH', defaultValue: 'develop', description: 'braincloud-unreal branch (eg. release/5.0)')
        string(name: 'UE4_TEST_BRANCH', defaultValue: 'ue4-tests', description: 'branch with unreal 4 project files')
        string(name: 'BC_LIB', defaultValue: '', description: 'Plugins/BCClient branch (blank for .gitmodules)')
        string(name: 'TEST_NAME', defaultValue: 'Authentication', description: 'test filter')
        choice(name: 'SERVER_ENVIRONMENT', choices: ['internal', 'prod'], description: 'Where to run tests?')
    }
    stages {

        stage('Tests on UE 5.3 Mac') {
            agent {
                label 'clientUnit'
            }
            environment {
			    PATH = "/Applications/CMake.app/Contents/bin:/usr/local/bin:${env.PATH}"
			    UE_INSTALL_PATH="/Users/Shared/Epic Games/UE_5.3"
                UE_EDITOR_CMD="UnrealEditor-Cmd"
                UE_VERSION="5.3"
                BRAINCLOUD_TOOLS="/Users/buildmaster/braincloud-client-master"
  			}
            steps {
                catchError(buildResult: 'SUCCESS', stageResult: 'FAILURE') {
                    //deleteDir()
                    checkout([$class: 'GitSCM', branches: [[name: '*/${TEST_BRANCH}']], extensions: [[$class: 'SubmoduleOption', disableSubmodules: false, parentCredentials: false, recursiveSubmodules: true, reference: '', trackingSubmodules: false]], userRemoteConfigs: [[url: 'https://github.com/getbraincloud/braincloud-unreal.git']]])
                    sh 'autobuild/checkout-submodule.sh ${BC_LIB}'
                    sh "${BRAINCLOUD_TOOLS}/bin/copy-ids.sh -o Source/BCSubsystem -p test -x h -s ${params.SERVER_ENVIRONMENT}"
                    sh 'autobuild/runtest.sh ${TEST_NAME}'
			    }
            }
            post {
                success {
                    //fileOperations([fileCopyOperation(excludes: '', flattenFiles: false, includes: '/Users/buildmaster/Library/Logs/Unreal\\ Engine/BCSubsystemServer/Mac_TestLog_UE_5.1.log', renameFiles: false, sourceCaptureExpression: '', targetLocation: 'saved/logs/Mac_TestLog_UE_5.1.log', targetNameExpression: '')])
                    archiveArtifacts artifacts: 'TestResults_Mac_5.3/index.json, saved/logs/TestLog_Mac_5.3.log', followSymlinks: false, allowEmptyArchive: true
               }
            }
        }

        stage('Tests on UE 5.2 Windows') {
            agent {
                label 'unrealWindows'
            }
            environment {
                UE_VERSION="5.2"
			    UE_INSTALL_PATH="C:\\ProgramFiles\\UE_5.2"
                UE_EDITOR_CMD="UnrealEditor"
                BRAINCLOUD_TOOLS="C:\\Users\\buildmaster\\braincloud-client-master"
            }
            steps {
                deleteDir()
                checkout([$class: 'GitSCM', branches: [[name: '*/${TEST_BRANCH}']], extensions: [[$class: 'SubmoduleOption', disableSubmodules: false, parentCredentials: false, recursiveSubmodules: true, reference: '', trackingSubmodules: false]], userRemoteConfigs: [[url: 'https://github.com/getbraincloud/braincloud-unreal.git']]])
                bat 'autobuild\\checkout-submodule.bat %BC_LIB%'
            	bat '%BRAINCLOUD_TOOLS%\\bin\\copy-ids.bat Source\\BCSubsystem test h internal'
            	bat 'autobuild\\runtest.bat %TEST_NAME%'
            }
            post {
                success {
                    archiveArtifacts artifacts: 'TestResults_Win64_5.2/index.json, saved/logs/TestLog_Win64_5.2.log', followSymlinks: false, allowEmptyArchive: true
               }
            }
        }

        stage('Tests on UE 5.1 Mac') {
            agent {
                label 'clientUnit'
            }
            environment {
			    PATH = "/Applications/CMake.app/Contents/bin:/usr/local/bin:${env.PATH}"
			    UE_INSTALL_PATH="/Users/Shared/Epic Games/UE_5.1"
                UE_EDITOR_CMD="UnrealEditor-Cmd"
                UE_VERSION="5.1"
                BRAINCLOUD_TOOLS="/Users/buildmaster/braincloud-client-master"
  			}
            steps {
                deleteDir()
                checkout([$class: 'GitSCM', branches: [[name: '*/${TEST_BRANCH}']], extensions: [[$class: 'SubmoduleOption', disableSubmodules: false, parentCredentials: false, recursiveSubmodules: true, reference: '', trackingSubmodules: false]], userRemoteConfigs: [[url: 'https://github.com/getbraincloud/braincloud-unreal.git']]])
			    sh 'autobuild/checkout-submodule.sh ${BC_LIB}'
                sh "${BRAINCLOUD_TOOLS}/bin/copy-ids.sh -o Source/BCSubsystem -p test -x h -s ${params.SERVER_ENVIRONMENT}"
			    sh 'autobuild/runtest.sh ${TEST_NAME}'
            }
            post {
                success {
                    //fileOperations([fileCopyOperation(excludes: '', flattenFiles: false, includes: '/Users/buildmaster/Library/Logs/Unreal\\ Engine/BCSubsystemServer/Mac_TestLog_UE_5.1.log', renameFiles: false, sourceCaptureExpression: '', targetLocation: 'saved/logs/Mac_TestLog_UE_5.1.log', targetNameExpression: '')])
                    archiveArtifacts artifacts: 'TestResults_Mac_5.1/index.json, saved/logs/TestLog_Mac_5.1.log', followSymlinks: false, allowEmptyArchive: true
               }
            }
        }

        stage('Tests on UE 4.27 Windows') {
            when {
                expression {
                    params.UE4_TEST_BRANCH != ''
                }
            }
            agent {
                label 'unrealWindows'
            }
            environment {
                UE_VERSION="4.27"
			    UE_INSTALL_PATH="C:\\ProgramFiles\\UE_4.27"
                UE_EDITOR_CMD="U4Editor-cmd"
                BRAINCLOUD_TOOLS="C:\\Users\\buildmaster\\braincloud-client-master"
            }
            steps {
                deleteDir()
                checkout([$class: 'GitSCM', branches: [[name: '*/${UE4_TEST_BRANCH}']], extensions: [[$class: 'SubmoduleOption', disableSubmodules: false, parentCredentials: false, recursiveSubmodules: true, reference: '', trackingSubmodules: false]], userRemoteConfigs: [[url: 'https://github.com/getbraincloud/braincloud-unreal.git']]])
                bat 'autobuild\\checkout-submodule.bat %BC_LIB%'
            	bat '%BRAINCLOUD_TOOLS%\\bin\\copy-ids.bat Source\\BCSubsystem test h internal'
            	bat 'autobuild\\runtest.bat %TEST_NAME%'
            }
            post {
                success {
                    archiveArtifacts artifacts: 'TestResults_Win64_4.27/index.json, saved/logs/TestLog_Win64_4.27.log', followSymlinks: false, allowEmptyArchive: true
               }
            }
        }
        // end stages
    }
    // end pipeline
}