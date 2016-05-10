#include "braincloud/internal/GUID.h"
#import <Foundation/Foundation.h>
#import <Foundation/NSString.h>
#import <Foundation/NSUUID.h>

namespace BrainCloud
{
	std::string GUID::generateGUID()
	{
		CFUUIDRef theUUID = CFUUIDCreate(NULL);
		CFStringRef str = CFUUIDCreateString(NULL, theUUID);
		CFRelease(theUUID);
		
		std::string guid = [[NSString stringWithFormat:@"%@",str] UTF8String];
        
        CFRelease(str);        
		return guid;
	}
}