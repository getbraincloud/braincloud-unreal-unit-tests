SRC_DIR=${1?Error: no src dir given}
APP_ID=${2?Error: no app id given}
SECRET_KEY=${3?Error: no secret key given}

cd $SRC_DIR

echo "#pragma once" >ids.h
echo "#define BRAINCLOUD_SERVER_URL \"https://api.internal.braincloudservers.com/dispatcherv2\"" >>ids.h
echo "#define BRAINCLOUD_APP_ID \"$APP_ID\"" >>ids.h
echo "#define BRAINCLOUD_APP_SECRET \"$SECRET_KEY\"" >>ids.h

echo "File ids.h created in $SRC_DIR"
cat ids.h
