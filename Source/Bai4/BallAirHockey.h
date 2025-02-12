// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BallAirHockey.generated.h"

UCLASS()
class BAI4_API ABallAirHockey : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABallAirHockey();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* BallCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* BallMeshComponent;

	UPROPERTY(EditAnyWhere, Category ="Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_WorldDynamic;

	UPROPERTY(Replicated)
	FVector Move;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY()
	AActor* PreActor = nullptr;
};
