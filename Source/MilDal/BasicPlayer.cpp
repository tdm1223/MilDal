// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPlayer.h"

// Sets default values
ABasicPlayer::ABasicPlayer()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerModel(TEXT("SkeletalMesh'/Game/Character/Monkey_Mesh.Monkey_Mesh'"));

    if (PlayerModel.Succeeded())
    {
        GetMesh()->SetSkeletalMesh(PlayerModel.Object);
    }
}

// Called when the game starts or when spawned
void ABasicPlayer::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ABasicPlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

