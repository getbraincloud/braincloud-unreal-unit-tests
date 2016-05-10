#include "braincloud/internal/GUID.h"
#include <iomanip>
#include <sstream>
#include <algorithm>

#if defined(WINAPI_FAMILY) || defined(WIN32)
#include <objbase.h>
#endif

// preston: use the crossguid library on android.
// it does support other platforms so a future enhancement would
// be to solely
//#ifdef __ANDROID
//#include "jni.h"
//#include "crossguid.h"
//#endif


std::string BrainCloud::GUID::generateGUID()
{
	unsigned char buffer[16] = { 0 };

#if defined(WINAPI_FAMILY) || defined(WIN32)
	UUID guid;
	CoCreateGuid(&guid);
	memcpy(buffer, &guid, 16);
#else
    // preston: for Android we should use crossguid lib to get the right thing...
    // just not sure how to get the JNIEnv pointer right now...

    for (int i = 0; i < 16; ++i)
    {
        buffer[i] = (unsigned char) (rand() % 255);
    }
#endif

	std::stringstream ss;
	ss << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[3];
	ss << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[2];
	ss << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[1];
	ss << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[0];
	ss << "-";
	ss << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[5];
	ss << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[4];
	ss << "-";
	ss << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[7];
	ss << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[6];
	ss << "-";
	ss << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[8];
	ss << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[9];
	ss << "-";
	ss << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[10];
	ss << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[11];
	ss << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[12];
	ss << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[13];
	ss << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[14];
	ss << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[15];

	return ss.str();
}

