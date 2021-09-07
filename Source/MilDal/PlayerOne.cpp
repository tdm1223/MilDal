// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerOne.h"

void APlayerOne::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ABasicPlayer::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ABasicPlayer::MoveRight);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABasicPlayer::StartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABasicPlayer::EndJump);
}