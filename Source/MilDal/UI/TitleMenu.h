#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleMenu.generated.h"

UCLASS()
class MILDAL_API UTitleMenu : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
        class UButton* Start;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
        class UButton* Option;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
        class UButton* Quit;
    virtual void NativeConstruct();

    UFUNCTION()
        void OnStart();
    UFUNCTION()
        void OnOption();
    UFUNCTION()
        void OnQuit();
};
