//
//  DefaultPinger.h
//  GameClientLib
//
//  Unimplemented version of the pinger
//

#ifndef _DEFAULTPINGER_H_
#define _DEFAULTPINGER_H_

#include "braincloud/internal/IPinger.h"

namespace BrainCloud
{
    class DefaultPinger final : public IPinger
    {
    public:
        // Always return 999
        int ping(const std::string& url) override;

    protected:
        friend class IPinger;

        DefaultPinger();
    };
}

#endif  // _DEFAULTPINGER_H_
