//
//  cURLPinger.h
//  GameClientLib
//

#ifndef _CURLPINGER_H_
#define _CURLPINGER_H_

#include "braincloud/internal/IPinger.h"

namespace BrainCloud
{
    class cURLPinger final : public IPinger
    {
    public:
        // Blocking call that returns a ping between 0 and 999 milliseconds
        int ping(const std::string& url) override;

    protected:
        friend class IPinger;

        cURLPinger();
    };
}

#endif  // _CURLPINGER_H_
