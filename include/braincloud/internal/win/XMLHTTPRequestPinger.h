//
//  XMLHTTPPinger.h
//  GameClientLib
//

#ifndef _XMLHTTPREQUESTPINGER_H_
#define _XMLHTTPREQUESTPINGER_H_

#include "braincloud/internal/IPinger.h"

namespace BrainCloud
{
    class XMLHTTPRequestPinger final : public IPinger
    {
    public:
        // Blocking call that returns a ping between 0 and 999 milliseconds
        int ping(const std::string& url) override;

    protected:
        friend class IPinger;

        XMLHTTPRequestPinger();
    };
}

#endif  // _XMLHTTPREQUESTLOADER_H_
