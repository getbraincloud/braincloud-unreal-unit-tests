
pipeline {
    agent none
    triggers {
        cron('H 20 * * 1-5') // nightly around 8 pm
        //pollSCM('H/5 * * * *') // check git every five minutes
    }
    parameters {
        string(name: 'BC_LIB', defaultValue: '', description: 'braincloud-unreal-plugin-src branch (blank for .gitmodules)')
        string(name: 'TEST_NAME', defaultValue: 'Authentication', description: 'test filter')
        choice(name: 'SERVER_ENVIRONMENT', choices: ['internal', 'prod'], description: 'Where to run tests?')
    }
    stages {
            
            
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
                checkout([$class: 'GitSCM', branches: [[name: '*/develop']], extensions: [[$class: 'SubmoduleOption', disableSubmodules: false, parentCredentials: false, recursiveSubmodules: true, reference: '', trackingSubmodules: false]], userRemoteConfigs: [[url: 'https://github.com/getbraincloud/braincloud-unreal.git']]])				
			    sh 'autobuild/checkout-submodule.sh ${BC_LIB}'
                sh "${BRAINCLOUD_TOOLS}/bin/copy-ids.sh -o Source/BCSubsystem -p test -x h -s ${params.SERVER_ENVIRONMENT}"
			    sh 'autobuild/runtest.sh ${TEST_NAME}'
            }
            post {
                success {
                    //fileOperations([fileCopyOperation(excludes: '', flattenFiles: false, includes: '/Users/buildmaster/Library/Logs/Unreal\\ Engine/BCSubsystemEditor/RunTests.log', renameFiles: false, sourceCaptureExpression: '', targetLocation: 'saved/logs/RunTests.log', targetNameExpression: '')])
                    //fileRenameOperation(destination: 'saved/logs/RunTests_Mac.log', source: 'saved/logs/RunTests.log')
                    folderRenameOperation(destination: 'TestResults_Mac', source: 'TestResults')
                    archiveArtifacts artifacts: 'TestResults_Mac/index.json', followSymlinks: false
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
                checkout([$class: 'GitSCM', branches: [[name: '*/develop']], extensions: [[$class: 'SubmoduleOption', disableSubmodules: false, parentCredentials: false, recursiveSubmodules: true, reference: '', trackingSubmodules: false]], userRemoteConfigs: [[url: 'https://github.com/getbraincloud/braincloud-unreal.git']]])				
                bat 'autobuild\\checkout-submodule.bat %BC_LIB%'
            	bat '%BRAINCLOUD_TOOLS%\\bin\\copy-ids.bat Source\\BCSubsystem test h internal'
            	bat 'autobuild\\runtest.bat %TEST_NAME%'
            }
            post {
                success {
                    //fileRenameOperation(destination: 'saved/logs/RunTests_UE5.log', source: 'saved/logs/RunTests.log')
                    folderRenameOperation(destination: 'TestResults_UE5', source: 'TestResults')
                    archiveArtifacts artifacts: 'TestResults_UE5/index.json', followSymlinks: false
                }
            }
        } 
                            
        stage('Tests on UE 4.27 Windows') {
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
                checkout([$class: 'GitSCM', branches: [[name: '*/ue4-tests']], extensions: [[$class: 'SubmoduleOption', disableSubmodules: false, parentCredentials: false, recursiveSubmodules: true, reference: '', trackingSubmodules: false]], userRemoteConfigs: [[url: 'https://github.com/getbraincloud/braincloud-unreal.git']]])				
                bat 'autobuild\\checkout-submodule.bat %BC_LIB%'
            	bat '%BRAINCLOUD_TOOLS%\\bin\\copy-ids.bat Source\\BCSubsystem test h internal'
            	bat 'autobuild\\runtest.bat %TEST_NAME%'
            }
            post {
                success {
                    //fileRenameOperation(destination: 'saved/logs/RunTests_UE4.log', source: 'saved/logs/RunTests.log')
                    folderRenameOperation(destination: 'TestResults_UE4', source: 'TestResults')
                   archiveArtifacts artifacts: 'TestResults_UE4/index.json', followSymlinks: false
                }
            }
        } 
        // end stages
    }
    // end pipeline
}