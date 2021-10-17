#include "MilDalGameInstance.h"
#include "MilDal/MilDal.h"

UMilDalGameInstance* UMilDalGameInstance::Instance = nullptr;

UMilDalGameInstance* UMilDalGameInstance::GetInstance()
{
    return UMilDalGameInstance::Instance;
}

void UMilDalGameInstance::Init()
{
    Super::Init();

    MD_LOG(Warning, TEXT("UMilDalGameInstance Init"));

    UMilDalGameInstance::Instance = this;

    GenerateManager();
}

void UMilDalGameInstance::GenerateManager()
{
    if (!MilDalGameManager)
    {
        MD_LOG(Warning, TEXT("UMilDalGameManager Generate"));
        MilDalGameManager = NewObject<UMilDalGameManager>(this, UMilDalGameManager::StaticClass());
    }
}

UMilDalGameManager* UMilDalGameInstance::GetMilDalGameManager()
{
    return MilDalGameManager;
}