pipeline {
    agent none
    //triggers {
        //cron('H 20 * * 1-5') // nightly around 8 pm
        //pollSCM('H/5 * * * *') // check git every five minutes
    //}
    parameters {
        string(name: 'TEST_BRANCH', defaultValue: 'develop', description: 'examples-unreal branch')
        string(name: 'UE4_TEST_BRANCH', defaultValue: 'ue4-tests', description: 'branch with unreal 4 project files')
        string(name: 'BC_LIB', defaultValue: '', description: 'braincloud-unreal-plugin-src branch (blank for .gitmodules)')
        choice(name: 'SERVER_ENVIRONMENT', choices: ['internal', 'prod'], description: 'Where to run tests?')
        string(name: 'GAME_MAP', defaultValue: 'AndroidTest', description: '')
        choice(name: 'PLATFORM', choices: ['all', 'Mac', 'Win64', 'iOS', 'Android'], description: 'Which platform to build?')
    }
    stages {

        stage('Mac App') {
                when {
                    expression {
                        params.TEST_BRANCH != '' &&
                        params.PLATFORM == 'Mac' ||
                        params.TEST_BRANCH != '' &&
                        params.PLATFORM == 'all'
                    }
                }
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
                    echo "---- building Demo App for Mac branch ${TEST_BRANCH} plugin ${BC_LIB}"
                    // deleteDir()  // deleting makes for a slow build, do this manually if needed
                    checkout([$class: 'GitSCM', branches: [[name: '*/${TEST_BRANCH}']], extensions: [[$class: 'SubmoduleOption', disableSubmodules: false, parentCredentials: false, recursiveSubmodules: true, reference: '', trackingSubmodules: false]], userRemoteConfigs: [[url: 'https://github.com/getbraincloud/braincloud-unreal.git']]])
                    sh 'autobuild/checkout-submodule.sh ${BC_LIB}'
                    sh "${BRAINCLOUD_TOOLS}/bin/copy-ids.sh -o Source/BCSubsystem -p test -x h -s ${params.SERVER_ENVIRONMENT}"
                    sh "autobuild/makebuild.sh BCSubsystem MAC $GAME_MAP"
                }
                post {
                    success {
                        //sh "${BRAINCLOUD_TOOLS}/bin/upload_package.sh BCSubsystem-ANDROID/Android/BCSubsystem-arm64.apk"
                        fileOperations([fileZipOperation(folderPath: "BCSubsystem-Mac", outputFolderPath: '.')])
                        archiveArtifacts allowEmptyArchive: true, artifacts: "BCSubsystem-Mac.zip", followSymlinks: false, onlyIfSuccessful: true
                    }
                }
           }

        stage('Android App') {
                when {
                    expression {
                        params.TEST_BRANCH != ''  &&
                        params.PLATFORM == 'Android' ||
                        params.TEST_BRANCH != ''  &&
                        params.PLATFORM == 'all'
                    }
                }
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
                    echo "---- building Demo App for Android branch ${TEST_BRANCH} plugin ${BC_LIB}"
                    // deleteDir()  // deleting makes for a slow build, do this manually if needed
                    checkout([$class: 'GitSCM', branches: [[name: '*/${TEST_BRANCH}']], extensions: [[$class: 'SubmoduleOption', disableSubmodules: false, parentCredentials: false, recursiveSubmodules: true, reference: '', trackingSubmodules: false]], userRemoteConfigs: [[url: 'https://github.com/getbraincloud/braincloud-unreal.git']]])
                    sh 'autobuild/checkout-submodule.sh ${BC_LIB}'
                    sh "${BRAINCLOUD_TOOLS}/bin/copy-ids.sh -o Source/BCSubsystem -p test -x h -s ${params.SERVER_ENVIRONMENT}"
                    sh "autobuild/makebuild.sh BCSubsystem ANDROID $GAME_MAP"
                }
                post {
                    success {
                        sh "${BRAINCLOUD_TOOLS}/bin/upload_package.sh BCSubsystem-ANDROID/Android/BCSubsystem-arm64.apk"
                        fileOperations([fileZipOperation(folderPath: "BCSubsystem-ANDROID", outputFolderPath: '.')])
                        archiveArtifacts allowEmptyArchive: true, artifacts: "BCSubsystem-ANDROID.zip", followSymlinks: false, onlyIfSuccessful: true
                    }
                }
           }

        stage('Windows UE 4.27') {
            when {
                expression {
                    params.UE4_TEST_BRANCH != ''  &&
                    params.PLATFORM == 'Win64' ||
                    params.UE4_TEST_BRANCH != ''  &&
                    params.PLATFORM == 'all'
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
            	bat 'autobuild\\makebuild.bat BCSubsystem Win64 %GAME_MAP%'
            }
            post {
                success {
                    fileOperations([fileZipOperation(folderPath: "BCSubsystem-Win64_${UE_VERSION}", outputFolderPath: '.')])
                    archiveArtifacts allowEmptyArchive: true, artifacts: "BCSubsystem-Win64_${UE_VERSION}.zip", followSymlinks: false, onlyIfSuccessful: true
                }
            }
        }

        // end stages
    }
    // end pipeline
}