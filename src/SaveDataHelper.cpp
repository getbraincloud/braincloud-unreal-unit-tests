#include "braincloud/internal/SaveDataHelper.h"

namespace BrainCloud
{
    SaveDataHelper* SaveDataHelper::s_instance = NULL;

    SaveDataHelper* SaveDataHelper::getInstance()
    {
        if (s_instance == NULL)
        {
            s_instance = SaveDataHelper::create();
        }

        return s_instance;
    }

    SaveDataHelper::SaveDataHelper()
    {
    }
}
