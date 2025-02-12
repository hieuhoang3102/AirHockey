// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ControllerC2Plus.generated.h"

/**
 * 
 */
UCLASS()
class BAI4_API AControllerC2Plus : public APlayerController
{
	GENERATED_BODY()
protected:
	AControllerC2Plus();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	
private:
	UPROPERTY()
	float ClientTimestamp = 0.0f;

	UPROPERTY()
	FVector LastDestination;

	FTimerHandle MyTimerHandle;

	void HandleTimer();

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerReceiveInput(const FVector& MouseLocation, float Timestamp);

	UFUNCTION(Server, Unreliable)
	void SideHandle(const FVector& LocationSideHandle);

	UPROPERTY(Replicated)
	FVector MouseLocationServer = {0,0,0};

	UPROPERTY()
	FVector MouseLocationClient = {0,0,0};

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(ReplicatedUsing = OnRep_Size)
	int Side = -1;

	UFUNCTION()
	void OnRep_Size();
};
