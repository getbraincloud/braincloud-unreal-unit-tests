PROJECT_NAME=${1?Error}
APP_ID=${2?Error}
SECRET_KEY=${3?Error}

cd Source/$PROJECT_NAME


echo "#pragma once" >ids.h


echo "#define BRAINCLOUD_SERVER_URL \"https://api.internal.braincloudservers.com/dispatcherv2\"" >>ids.h
echo "#define BRAINCLOUD_APP_ID \"$APP_ID\"" >>ids.h
echo "#define BRAINCLOUD_APP_SECRET \"$SECRET_KEY\"" >>ids.h

echo "#define BRAINCLOUD_CHILD_APP_ID \"\"" >>ids.h
echo "#define BRAINCLOUD_CHILD_APP_SECRET \"\"" >>ids.h
echo "#define BRAINCLOUD_PARENT_LEVEL_NAME \"\"" >>ids.h
echo "#define BRAINCLOUD_PEER_NAME \"\"" >>ids.h
echo "#define BRAINCLOUD_SERVER_NAME \"\"" >>ids.h
echo "#define BRAINCLOUD_SERVER_SECRET \"\"" >>ids.h
echo "#define BRAINCLOUD_S2S_SERVER \"\"" >>ids.h

echo "#define TESTFILE_SERVER_URL \"\"" >>ids.h
echo "#define TESTFILE_APP_ID \"\"" >>ids.h
echo "#define TESTFILE_APP_SECRET \"\"" >>ids.h

echo "File ids.h created in Source/$PROJECT_NAME"

cat ids.h
