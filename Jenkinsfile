
pipeline {
    agent none
    triggers {
        cron('H 2 * * 1-5') // nightly around 2 am
        pollSCM('H/5 * * * *') // check git every five minutes
    }
        parameters {
        string(name: 'BC_LIB', defaultValue: '', description: 'braincloud-unreal-plugin-src branch (blank for .gitmodules)')
        string(name: 'BRANCH_NAME', defaultValue: 'develop', description: 'braincloud-unreal tests source')
        string(name: 'UE4_BRANCH', defaultValue: 'ue4-tests', description: 'braincloud-unreal tests source')
        string(name: 'TEST_NAME', defaultValue: 'Test_BCAuth', description: 'test filter')
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
  			}
            steps {
                deleteDir()
                checkout([$class: 'GitSCM', branches: [[name: '*/${BRANCH_NAME}']], extensions: [[$class: 'SubmoduleOption', disableSubmodules: false, parentCredentials: false, recursiveSubmodules: true, reference: '', trackingSubmodules: false]], userRemoteConfigs: [[url: 'https://github.com/getbraincloud/braincloud-unreal.git']]])				
			    sh 'autobuild/checkout-submodule.sh ${BC_LIB}'
                sh '~/braincloud-bin/setupunrealtests.sh'
			    sh 'autobuild/runtest.sh ${TEST_NAME}'
            }
            post {
	      		success {
    	    		junit testResults: 'build/tests/results.xml', skipPublishingChecks: true
      			}
            }
        } 
        // end stages
    }
    // end pipeline
}