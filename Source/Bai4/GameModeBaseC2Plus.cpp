// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeBaseC2Plus.h"
#include "ControllerC2Plus.h"


void AGameModeBaseC2Plus::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	Side++;
	ControllersRef.AddUnique(NewPlayer);
	AControllerC2Plus* PlayerController = Cast<AControllerC2Plus>(NewPlayer);
	//PlayerController->Side = Side;
	
}


//UE_LOG(LogTemp, Warning, TEXT("Curent number of players: %d"), ControllersRef.Num());

// Nếu đã có ít nhất một người chơi, set vị trí cho người chơi đầu tiên
// if (ControllersRef.Num() > 0)
// {
//     AController* FirstPlayer = ControllersRef[0];
//     if (FirstPlayer)
//     {
//         APawn* FirstPlayerPawn = FirstPlayer->GetPawn();
//         if (FirstPlayerPawn)
//         {
//             // Set vị trí cho Pawn của người chơi đầu tiên
//             FirstPlayerPawn->SetActorLocation(PawnLocation1);
//             UE_LOG(LogTemp, Log, TEXT("First player location set to: %s"), *PawnLocation1.ToString());
//         }
//     }
// }
//
// // Nếu có 2 người chơi, set vị trí cho người chơi thứ hai
// if (ControllersRef.Num() > 1)
// {
//     AController* SecondPlayer = ControllersRef[1];
//     if (SecondPlayer)
//     {
//         APawn* SecondPlayerPawn = SecondPlayer->GetPawn();
//         if (SecondPlayerPawn)
//         {
//             // Set vị trí cho Pawn của người chơi thứ hai
//             SecondPlayerPawn->SetActorLocation(PawnLocation2);
//             UE_LOG(LogTemp, Log, TEXT("Second player location set to: %s"), *PawnLocation2.ToString());
//         }
//     }
// }
