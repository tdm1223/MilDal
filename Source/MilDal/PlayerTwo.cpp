// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTwo.h"

void APlayerTwo::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForwardTwo", this, &ABasicPlayer::MoveForward);
    PlayerInputComponent->BindAxis("MoveRightTwo", this, &ABasicPlayer::MoveRight);
    PlayerInputComponent->BindAction("JumpTwo", IE_Pressed, this, &ABasicPlayer::StartJump);
    PlayerInputComponent->BindAction("JumpTwo", IE_Released, this, &ABasicPlayer::EndJump);
}