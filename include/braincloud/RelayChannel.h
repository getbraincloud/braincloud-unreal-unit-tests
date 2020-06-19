// Copyright 2020 bitHeads, Inc. All Rights Reserved.

#ifndef _RELAYCHANNEL_H_
#define _RELAYCHANNEL_H_

namespace BrainCloud
{
    enum class eRelayChannel : int
    {
        HighPriority1 = 0,
        HighPriority2 = 1,
        NormalPriority = 2,
        LowPriority = 3
    };
};

#endif /* _RELAYCHANNEL_H_ */
