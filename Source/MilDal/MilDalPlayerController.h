#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MilDalPlayerController.generated.h"

UCLASS()
class MILDAL_API AMilDalPlayerController : public APlayerController
{
    GENERATED_BODY()
public:
    AMilDalPlayerController();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
        TSubclassOf<class UMainWidget> HudWidgetClass;

    UPROPERTY()
        class UMainWidget* MainWidget;

public:
    virtual void BeginPlay();
    UMainWidget* GetMainWidget() const;
};
