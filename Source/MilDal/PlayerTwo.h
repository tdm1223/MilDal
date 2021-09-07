// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicPlayer.h"
#include "PlayerTwo.generated.h"

/**
 *
 */
UCLASS()
class MILDAL_API APlayerTwo : public ABasicPlayer
{
    GENERATED_BODY()

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
