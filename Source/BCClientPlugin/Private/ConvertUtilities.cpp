#include "ConvertUtilities.h"

FString ConvertUtilities::BCBytesToString(const uint8 *in, int32 count)
{
	FString result2;
	result2.Empty(count);
	while (count)
	{
        result2 += ANSICHAR(*in);
		++in;
		--count;
	}
	
	return result2;
}

int32 ConvertUtilities::BCStringToBytes(const FString &in_string, uint8 *out_bytes, int32 in_maxBufferSize)
{
	int32 numBytes = 0;
	const TCHAR *charPos = *in_string;

	while (*charPos && numBytes < in_maxBufferSize)
	{
		out_bytes[numBytes] = (uint8)(*charPos);
		charPos++;
		++numBytes;
	}
	return numBytes;
}
