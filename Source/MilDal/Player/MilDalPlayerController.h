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
        TSubclassOf<class UMainWidget> MainWidgetClass;

    UPROPERTY()
        class UMainWidget* MainWidget;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
        TSubclassOf<class UPauseMenu> PauseWidgetClass;

    UPROPERTY()
        class UPauseMenu* PauseWidget;

public:
    virtual void BeginPlay();
    virtual void SetupInputComponent() override;
    UMainWidget* GetMainWidget() const;
    void ChangeInputMode(bool bGameMode);
    void OnGamePause();

    FInputModeGameOnly GameInputMode;
    FInputModeUIOnly UIInputMode;
};
