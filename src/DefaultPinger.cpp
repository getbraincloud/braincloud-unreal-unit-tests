#include "braincloud/internal/DefaultPinger.h"

namespace BrainCloud
{
    IPinger* IPinger::create()
    {
        return new DefaultPinger();
    }

    DefaultPinger::DefaultPinger() {}

    int DefaultPinger::ping(const std::string& url)
    {
        return 999;
    }
}
