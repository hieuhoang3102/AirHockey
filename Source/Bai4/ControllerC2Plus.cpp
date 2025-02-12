// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllerC2Plus.h"
#include "Handle.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameModeBaseC2Plus.h"
#include "ShaderPrintParameters.h"
#include "Net/UnrealNetwork.h"

AControllerC2Plus::AControllerC2Plus()
{
    bReplicates = true;
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;
}

void AControllerC2Plus::BeginPlay()
{
    Super::BeginPlay();
    GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &AControllerC2Plus::HandleTimer, 0.016f, true);
}

void AControllerC2Plus::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AControllerC2Plus::HandleTimer()
{
    ClientTimestamp += 1;
    
    if (IsValid(GetPawn()))
    {
        if (!HasAuthority())
        {
            FVector WorldLocation, WorldDirection;

            // Get the mouse position in the world
            DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

            FHitResult HitResult;
            const FVector& StartLocation = WorldLocation;
            const FVector& EndLocation = StartLocation + WorldDirection * 10000.0f;

            // Perform a trace (similar to the "Get Hit Result Under Cursor by Channel" node)
            bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility);

            if (bHit)
            {
                MouseLocationClient = HitResult.Location;
                MouseLocationClient.Z = 50.0f; // Setting Z to 50 as shown in the "Set Actor Location" node
                if (MouseLocationClient.X < 1200.0f)
                {
                    MouseLocationClient.X = 1200.0f;
                }
                else if (MouseLocationClient.X > 1790.0f)
                {
                    MouseLocationClient.X = 1790.0f;
                }
                else if (MouseLocationClient.Y < 1050.0f)
                {
                    MouseLocationClient.Y = 1050.0f;
                }
                else if (MouseLocationClient.Y > 2350.0f)
                {
                    MouseLocationClient.Y = 2350.0f;
                }

                LastDestination = MouseLocationClient;
            
                if (GetPawn())
                {
                    GetPawn()->SetActorLocation(MouseLocationClient);
                }

                ServerReceiveInput(MouseLocationClient, ClientTimestamp);
                Cast<AHandle>(GetPawn())->Request.Add(FHandleRepPosition(ClientTimestamp, LastDestination));
            }
        }
    }
}

void AControllerC2Plus::ServerReceiveInput_Implementation(const FVector& MouseLocation, float Timestamp)
{
    MouseLocationServer = MouseLocation;
    MouseLocationServer.Z = 50.0f;
    if(MouseLocationServer.X < 1200.0f)
    {
        MouseLocationServer.X = 1200.0f;
    }
    else if(MouseLocationServer.X > 1790.0f)
    {
        MouseLocationServer.X = 1790.0f;
    }
    else if(MouseLocationServer.Y < 1050.0f)
    {
        MouseLocationServer.Y = 1050.0f;
    }
    else if(MouseLocationServer.Y > 2350.0f)
    {
        MouseLocationServer.Y = 2350.0f;
    }
    if(GetPawn())
    {
        // Đặt vị trí đã xác thực lại trên server
        GetPawn()->SetActorLocation(MouseLocationServer);
        Cast<AHandle>(GetPawn())->RepPosition = FHandleRepPosition(Timestamp, MouseLocationServer);
    }
}

bool AControllerC2Plus::ServerReceiveInput_Validate(const FVector& MouseLocation, float Timestamp)
{
    return true;
}

void AControllerC2Plus::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AControllerC2Plus, MouseLocationServer);
    DOREPLIFETIME(AControllerC2Plus, Side);
}

void AControllerC2Plus::OnRep_Size()
{
    if (IsValid(GetPawn()))
    {
        if (Side == 0)
        {
            GetPawn()->SetActorLocation({1500.0f, 1152.0f, 32.0f});
            SideHandle({1500.0f, 1152.0f, 32.0f});
        }
        if (Side == 1) 
        {
            GetPawn()->SetActorLocation({1500.0f, 2152.0f, 32.0f});
            SideHandle({1500.0f, 2152.0f, 32.0f});
        }
    }
}

void AControllerC2Plus::SideHandle_Implementation(const FVector& LocationSideHandle)
{
    GetPawn()->SetActorLocation(LocationSideHandle);
}
