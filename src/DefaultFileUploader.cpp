#include "braincloud/internal/IFileUploader.h"

#include <iostream>

namespace BrainCloud
{
    IFileUploader* IFileUploader::create()
    {
        std::cerr << "#BCC File upload operations not supported on this platform" << std::endl;
        return nullptr;
    }
}
