//
//  StringUtil.h
//  BrainCloudLib
//
#ifndef _STRINGUTIL_H_
#define _STRINGUTIL_H_

#ifdef UNICODE
#define MGC_CHAR wchar_t
#define MGC_PCSZ const wchar_t*
//... other wide functions
#else // not UNICODE
#define MGC_CHAR char
#define MGC_PCSZ const char*
//... other non-wide functions
#endif

#ifndef MGC_SIZEOFWCHAR
#if __SIZEOF_WCHAR_T__ == 4 || __WCHAR_MAX__ > 0x10000
#define MGC_SIZEOFWCHAR 4
#else
#define MGC_SIZEOFWCHAR 2
#endif
#endif

#include <string>

namespace BrainCloud {

//  void convertToUTF8(MGC_PCSZ text, std::string * utf8Result) {
//      if (text == NULL) {
//          return;
//      }
//#if MGC_SIZEOFWCHAR == 4 // sizeof(wchar_t) == 4
//      //... treat wchar_t string as UTF-32
//#else // sizeof(wchar_t) == 2
//      //... treat wchar_t string as UTF-16
//      std::vector<unsigned char> buf;
//      utf8::unchecked::utf16to8(text, text + wcslen(text), back_inserter(buf));
//      utf8Result->clear();
//      for(std::vector<unsigned char>::iterator it = buf.begin(); it != buf.end(); ++it) {
//          utf8Result->push_back(*it);
//      }
//#endif
//  }
    
    class StringUtil {
    public:
        static bool IsOptionalParameterValid(const char * in_param);
        static bool IsOptionalParameterValid(std::string in_param);
    };

}

#endif  // _STRINGUTIL_H_
