// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCBlueprintSupportPrivatePCH.h"
#include "BCBlueprintCallProxyBase.h"
#include "BlueprintFunctionNodeSpawner.h"
#include "BlueprintActionDatabaseRegistrar.h"

#include "K2Node_BrainCloudCall.h"

#define LOCTEXT_NAMESPACE "K2Node"

UK2Node_BrainCloudCall::UK2Node_BrainCloudCall(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    ProxyActivateFunctionName = NAME_None;
}

void UK2Node_BrainCloudCall::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    // these nested loops are combing over the same classes/functions the
    // FBlueprintActionDatabase does; ideally we save on perf and fold this in
    // with FBlueprintActionDatabase, but we want to keep the modules separate
    for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
    {
        UClass* Class = *ClassIt;
        if (!Class->IsChildOf<UBCBlueprintCallProxyBase>() || Class->HasAnyClassFlags(CLASS_Abstract))
        {
            continue;
        }

        for (TFieldIterator<UFunction> FuncIt(Class, EFieldIteratorFlags::ExcludeSuper); FuncIt; ++FuncIt)
        {
            UFunction* Function = *FuncIt;
            if (!Function->HasAnyFunctionFlags(FUNC_Static))
            {
                continue;
            }

            // to keep from needlessly instantiating a UBlueprintNodeSpawner, first   
            // check to make sure that the registrar is looking for actions of this type
            // (could be regenerating actions for a specific asset, and therefore the 
            // registrar would only accept actions corresponding to that asset)
            if (!ActionRegistrar.IsOpenForRegistration(Function))
            {
                continue;
            }

            UObjectProperty* ReturnProperty = Cast<UObjectProperty>(Function->GetReturnProperty());
            // see if the function is a static factory method for online proxies
            bool const bIsProxyFactoryMethod = (ReturnProperty != nullptr) && ReturnProperty->PropertyClass->IsChildOf<UBCBlueprintCallProxyBase>();

            if (bIsProxyFactoryMethod)
            {
                UBlueprintNodeSpawner* NodeSpawner = UBlueprintFunctionNodeSpawner::Create(Function);
                check(NodeSpawner != nullptr);
                NodeSpawner->NodeClass = GetClass();

                auto CustomizeAcyncNodeLambda = [](UEdGraphNode* NewNode, bool bIsTemplateNode, TWeakObjectPtr<UFunction> FunctionPtr)
                {
                    UK2Node_BrainCloudCall* AsyncTaskNode = CastChecked<UK2Node_BrainCloudCall>(NewNode);
                    if (FunctionPtr.IsValid())
                    {
                        UFunction* Func = FunctionPtr.Get();
                        UObjectProperty* ReturnProp = CastChecked<UObjectProperty>(Func->GetReturnProperty());

                        AsyncTaskNode->ProxyFactoryFunctionName = Func->GetFName();
                        AsyncTaskNode->ProxyFactoryClass = Func->GetOuterUClass();
                        AsyncTaskNode->ProxyClass = ReturnProp->PropertyClass;
                    }
                };

                TWeakObjectPtr<UFunction> FunctionPtr = Function;
                NodeSpawner->CustomizeNodeDelegate = UBlueprintNodeSpawner::FCustomizeNodeDelegate::CreateStatic(CustomizeAcyncNodeLambda, FunctionPtr);

                // @TODO: since this can't be folded into FBlueprintActionDatabase, we
                //        need a way to associate these spawners with a certain class
                ActionRegistrar.AddBlueprintAction(Function, NodeSpawner);
            }
        }
    }
}

#undef LOCTEXT_NAMESPACE
