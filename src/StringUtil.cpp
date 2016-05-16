
#include "braincloud/internal/StringUtil.h"

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
    
    bool StringUtil::IsOptionalParameterValid(const char * in_param)
    {
        if (in_param == 0 || *in_param == '\0')
        {
            return false;
        }
        return true;
    }
    
    bool StringUtil::IsOptionalParameterValid(std::string in_param)
    {
        if (in_param.length() <= 0)
        {
            return false;
        }
        return true;
    }

}