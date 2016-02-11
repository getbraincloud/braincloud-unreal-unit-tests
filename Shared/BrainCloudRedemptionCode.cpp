#include "BrainCloudRedemptionCode.h"
#include "BrainCloudClient.h"
#include "StringUtil.h"


namespace BrainCloud
{
    void BrainCloudRedemptionCode::redeemCode(const char* in_scanCode, const char* in_codeType, const char* in_jsonCustomRedemptionInfo, IServerCallback * in_callback)
    {
        Json::Value message;

        message[OperationParam::RedemptionCodeServiceScanCode.getValue()] = in_scanCode;
        message[OperationParam::RedemptionCodeServiceCodeType.getValue()] = in_codeType;
        
        if (StringUtil::IsOptionalParameterValid(in_jsonCustomRedemptionInfo))
        {
            Json::Reader reader;
            Json::Value parsedInfo;
            reader.parse(in_jsonCustomRedemptionInfo, parsedInfo);
            message[OperationParam::RedemptionCodeServiceCustomRedemptionInfo.getValue()] = parsedInfo;
        }

        ServerCall * sc = new ServerCall( ServiceName::RedemptionCode, ServiceOperation::RedeemCode, message, in_callback );
        BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
    }
    
    void BrainCloudRedemptionCode::getRedeemedCodes(const char* in_codeType, IServerCallback * in_callback)
    {
        Json::Value message;
        
        if (StringUtil::IsOptionalParameterValid(in_codeType))
        {
            message[OperationParam::RedemptionCodeServiceCodeType.getValue()] = in_codeType;
        }
        
        ServerCall * sc = new ServerCall( ServiceName::RedemptionCode, ServiceOperation::GetRedeemedCodes, message, in_callback );
        BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
    }
}