#include "braincloud/internal/GUID.h"

#include <iomanip>
#include <sstream>
#include <algorithm>

namespace BrainCloud
{
    std::string GUID::GUIDToString(const unsigned char* buffer)
    {
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
}
