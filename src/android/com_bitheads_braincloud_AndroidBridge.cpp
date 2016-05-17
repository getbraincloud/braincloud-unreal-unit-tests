#include "braincloud/internal/android/com_bitheads_braincloud_AndroidBridge.h"

#if defined(__ANDROID__)

#include <stdio.h>
#include "braincloud/BrainCloudClient.h"

using namespace BrainCloud;

JNIEXPORT void JNICALL Java_com_bitheads_braincloud_AndroidBridge_setCountryCode
(JNIEnv *env, jclass jClass, jstring jCountryCode)
{
    int len = env->GetStringUTFLength(jCountryCode);
    if (len > 0 && len < 128)
    {
        char buf[128];
        const char *str = env->GetStringUTFChars(jCountryCode, NULL);

        BrainCloudClient *client = BrainCloudClient::getInstance();
        client->setCountryCode(str);

        env->ReleaseStringUTFChars(jCountryCode, str);
    }
}

JNIEXPORT void JNICALL Java_com_bitheads_braincloud_AndroidBridge_setLanguageCode
  (JNIEnv * env, jclass jClass, jstring jLanguageCode)
{
    int len = env->GetStringUTFLength(jLanguageCode);
    if (len > 0 && len < 128)
    {
        char buf[128];
        const char *str = env->GetStringUTFChars(jLanguageCode, NULL);

        BrainCloudClient *client = BrainCloudClient::getInstance();
        client->setLanguageCode(str);

        env->ReleaseStringUTFChars(jLanguageCode, str);
    }
}

JNIEXPORT void JNICALL Java_com_bitheads_braincloud_AndroidBridge_setTimezoneOffset
  (JNIEnv * env, jclass jClass, jfloat jTimezoneOffset)
{
    BrainCloudClient *client = BrainCloudClient::getInstance();
    client->setTimezoneOffset(jTimezoneOffset);
}

#endif
