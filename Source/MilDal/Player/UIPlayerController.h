#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UIPlayerController.generated.h"

UCLASS()
class MILDAL_API AUIPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AUIPlayerController();
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
        TSubclassOf<class UTitleMenu> UITitleClass;

    UPROPERTY()
        class UTitleMenu* UITitleInstance;
};
