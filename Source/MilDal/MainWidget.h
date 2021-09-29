#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

UCLASS()
class MILDAL_API UMainWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere)
        class UCanvasPanel* PlayerOneLifePanel;
    UPROPERTY(VisibleAnywhere)
        class UCanvasPanel* PlayerTwoLifePanel;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
        class UTextBlock* PlayerOneLifeText;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
        class UTextBlock* PlayerTwoLifeText;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
        class UImage* Image;

    virtual void NativeConstruct() override;

    void SetPlayerOneLifeText(int InLife);
    void SetPlayerTwoLifeText(int InLife);
};
