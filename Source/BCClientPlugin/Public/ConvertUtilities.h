#pragma once

class BCCLIENTPLUGIN_API ConvertUtilities
{
public:
    static FString BCBytesToString(const uint8 *in, int32 count);
    static int32 BCStringToBytes(const FString &in_string, uint8 *out_bytes, int32 in_maxBufferSize);
};
