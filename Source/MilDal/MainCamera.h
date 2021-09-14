// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "MainCamera.generated.h"

UCLASS()
class MILDAL_API AMainCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    // ToDo : 적절한 스피드를 찾은 후에는 내부 변수로 넣어야 한다.
    UPROPERTY(EditAnywhere)
    float MoveSpeed;

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* BoxComponent;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* CameraComponent;

private:
    FVector CurrentLocation;
};
