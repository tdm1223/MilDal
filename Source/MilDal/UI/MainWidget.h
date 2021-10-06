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
        class ULifePanel* PlayerOneLifePanel;
    UPROPERTY(VisibleAnywhere)
        class ULifePanel* PlayerTwoLifePanel;

    virtual void NativeConstruct() override;

    void SetPlayerOneLife(int InLife);
    void SetPlayerTwoLife(int InLife);
};
