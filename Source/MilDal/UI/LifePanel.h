#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LifePanel.generated.h"

UCLASS()
class MILDAL_API ULifePanel : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
        class UImage* LifeOne;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
        class UImage* LifeTwo;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
        class UImage* LifeThree;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
        class UImage* LifeFour;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
        class UImage* LifeFive;

    virtual void NativeConstruct();

    TArray<class UImage*> LifeArray;
};
