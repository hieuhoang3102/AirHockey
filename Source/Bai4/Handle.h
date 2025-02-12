// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"

#include "Handle.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FHandleRepPosition
{
	GENERATED_BODY()
	UPROPERTY(Blueprintable, BlueprintReadOnly)
	int TimeStamp;
	UPROPERTY(Blueprintable, BlueprintReadOnly)
	FVector Position;
	FHandleRepPosition():TimeStamp(0),Position({0,0,0})
	{
	}
	FHandleRepPosition(const int InTime, const FVector& InPosition)
	{
		TimeStamp = InTime;
		Position = InPosition;
	}
};

USTRUCT(Blueprintable, BlueprintType)
struct FHandleMovementState
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
	FVector Position;
	UPROPERTY(BlueprintReadWrite)
	FVector Velocity;
};


UCLASS()
class BAI4_API AHandle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHandle();

	UPROPERTY(ReplicatedUsing = OnRep_RepPosition)
	FHandleRepPosition RepPosition;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRep_RepPosition();
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* HandleCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* HandleMeshComponent;

	TArray<FHandleRepPosition> Request;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FVector GetHandleVelocity() const;
private:
	FVector PreviousPosition;
	FVector CurrentPosition;
	FVector HandleVelocity;
	float HandleSpeed;

	UFUNCTION()
	void CalculateVelocity(float DeltaTime);
};
