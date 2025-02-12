// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PackageMigrationContext.h"
#include "GameFramework/GameMode.h"
#include "GameModeBaseC2Plus.generated.h"

/**
 * 
 */
UCLASS()
class BAI4_API AGameModeBaseC2Plus : public AGameMode
{
	GENERATED_BODY()
	
protected:
	virtual void OnPostLogin(AController* NewPlayer) override;

	UPROPERTY()
	TArray<AController*> ControllersRef;

	// UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AirHockey")
	// int32 MinimumNumberOfPlayer = 2;

public:

private:	
	UPROPERTY()
	FVector PawnLocation1 = {1500, 1152, 32};

	UPROPERTY()
	FVector PawnLocation2 = {1500, 2152, 32};

	UPROPERTY()
	int Side = -1;
};
