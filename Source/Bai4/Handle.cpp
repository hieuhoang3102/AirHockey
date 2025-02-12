// Fill out your copyright notice in the Description page of Project Settings.


#include "Handle.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AHandle::AHandle()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Thiết lập replication
	bReplicates = true;
	SetReplicateMovement(true);

	HandleCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Handle Collision"));
	SetRootComponent(HandleCollision);

	HandleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Handle Mesh"));
	HandleMeshComponent->SetupAttachment(HandleCollision);
}

// Called when the game starts or when spawned
void AHandle::BeginPlay()
{
	Super::BeginPlay();
	PreviousPosition = GetActorLocation();
}

void AHandle::OnRep_RepPosition()
{
	if(IsValid(GetController()))
	{
		int FoundIndex = INDEX_NONE;
		if(!Request.IsEmpty())
		{
			for(int i = 0; i < Request.Num(); i++){
				const FHandleRepPosition Check = Request[i];
				if(Check.TimeStamp == RepPosition.TimeStamp)
				{
					FoundIndex = i;
					if((Check.Position - RepPosition.Position).SquaredLength() > 0.01f)
					{
						SetActorLocation(RepPosition.Position);
					}
					break;
				}
			}
		}
		if (FoundIndex != INDEX_NONE)
		{
			Request.RemoveAt(0, FoundIndex+1);
		}
		
	}
	else
	{
		if(!Request.IsEmpty())
		{
			if(Request[0].TimeStamp < RepPosition.TimeStamp)
			{
				Request[0] = RepPosition;
			}
		}
		else
		{
			Request.Add(RepPosition);
		}
	}
}

// Called every frame
void AHandle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(GetNetMode() >= NM_Client)
	{
		if(!IsValid(GetController())&& !Request.IsEmpty())
		{
			SetActorLocation(FMath::Lerp(GetActorLocation(), Request[0].Position, DeltaTime *15));
		}
	}

	// Cập nhật vị trí hiện tại
	CurrentPosition = GetActorLocation();

	// Tính toán vận tốc dựa trên thay đổi vị trí
	CalculateVelocity(DeltaTime);

	// Cập nhật vị trí trước đó cho khung hình tiếp theo
	PreviousPosition = CurrentPosition;
}

// Called to bind functionality to input
void AHandle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AHandle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHandle, RepPosition);
}

void AHandle::CalculateVelocity(float DeltaTime)
{
	if (DeltaTime > 0.0f)
	{
		// Tính vận tốc bằng cách lấy chênh lệch vị trí chia cho thời gian giữa các khung hình
		HandleVelocity = (CurrentPosition - PreviousPosition) / DeltaTime;

		// Tính tốc độ (độ lớn của vector vận tốc)
		HandleSpeed = HandleVelocity.Size();
	}
	else
	{
		HandleVelocity = FVector::ZeroVector;
		HandleSpeed = 0.0f;
	}
}

FVector AHandle::GetHandleVelocity() const
{
	return HandleVelocity;
} 
