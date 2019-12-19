//
//  nsPinger.h
//  GameClientLib
//

#ifndef _DEFAULTPINGER_H_
#define _DEFAULTPINGER_H_

#include "braincloud/internal/IPinger.h"

namespace BrainCloud
{
    class nsPinger final : public IPinger
    {
    public:
        // Blocking call that returns a ping between 0 and 999 milliseconds
        int ping(const std::string& url) override;

    protected:
        friend class IPinger;

        nsPinger();
    };
}

#endif  // _DEFAULTPINGER_H_
