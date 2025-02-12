// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreArea.h"


// Sets default values
AScoreArea::AScoreArea()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ScoreAreaCollision = CreateDefaultSubobject< UBoxComponent>(TEXT("Wall Collision"));
	SetRootComponent(ScoreAreaCollision);

	ScoreAreaMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Mesh"));
	ScoreAreaMeshComponent->SetupAttachment(ScoreAreaCollision);
}

// Called when the game starts or when spawned
void AScoreArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScoreArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

