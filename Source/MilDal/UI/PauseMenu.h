#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

UCLASS()
class MILDAL_API UPauseMenu : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
        class UButton* Resume;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
        class UButton* Title;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
        class UButton* Quit;
    virtual void NativeConstruct();

    UFUNCTION()
        void OnResume();

    UFUNCTION()
        void OnTitle();

    UFUNCTION()
        void OnQuit();
};
