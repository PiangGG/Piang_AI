// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AAIPawn::AAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

   this->InitComponent();
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (bFaceTargetActor)
	{
		if (GetWorld()->GetFirstLocalPlayerFromController()->GetPlayerController(GetWorld())->GetPawn()&&GetWorld()->GetFirstLocalPlayerFromController()&&GetWorld())
		{
			RotatorToActor();
		}
	}*/
}

// Called to bind functionality to input
void AAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIPawn::InitComponent()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//骨骼网格体
	Mesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetSkeletalMesh(LoadObject<USkeletalMesh>(NULL,TEXT("SkeletalMesh'/Game/GongPan_character/mask/mesh/mask3.mask3'")));
	Mesh->SetAnimClass(LoadClass<UAnimInstance>(NULL,TEXT("AnimBlueprint'/Game/BP/Piang/MianJuYingDao/Animation/BP_MaskAnimation.BP_MaskAnimation_C'")));

	//MoveMent
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
}

void AAIPawn::RotatorToActor()
{
	if (RotatorTargetActor)
	{
		FVector StartPoint =  GetActorLocation();
		FVector EndPoint = RotatorTargetActor->GetActorLocation();

		FRotator CurrentRotator = GetActorRotation();
		FRotator FaceRotator =  UKismetMathLibrary::FindLookAtRotation(StartPoint,EndPoint);

		CurrentRotator = FMath::RInterpConstantTo(CurrentRotator,FaceRotator,GetWorld()->GetDeltaSeconds(),1.0f);
		SetActorRotation(CurrentRotator);

		if (CurrentRotator.Equals(FaceRotator))
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle_RotatorToActor);
			bCanOperctor = true;
		}
	}
}

void AAIPawn::RotatorToActor(AActor* Actor,float RotatorRate)
{
	
	if (!bCanOperctor)return;
	bCanOperctor = false;
	
	BP_SetRotatorTargetActor(Actor);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_RotatorToActor,this,&AAIPawn::RotatorToActor,RotatorRate,true);
}

void AAIPawn::MoveToActor()
{
	if (bCanOperctor)
	{
		if (Movement&&MoveTargetActor)
		{
			if (FVector::Distance(BP_GetMoveTargetActor()->GetActorLocation(),GetActorLocation())<100)
			{
				return;
			}
			//Movement->AddInputVector(FRotator(0.0f,GetActorRotation().Yaw,0.0f).Vector(),false);
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), MoveTargetActor->GetActorLocation());
		}
	}
}

void AAIPawn::MoveToActor(AActor* Actor,float MoveRate)
{
	BP_SetMoveTargetActor(Actor);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_MoveToActor,this,&AAIPawn::MoveToActor,MoveRate,true);
}

void AAIPawn::WaitForPlayer(AActor* TargetActor)
{
	
}

void AAIPawn::ChangeAiPawnState(EAIPawnState TargetState,AActor* MoveActor,AActor* RotatorActor)
{
	switch (TargetState)
	{
		case EAIPawnState::EFollow:
			
			break;
		case EAIPawnState::ETalk:
			
			break;
		
		case EAIPawnState::EWait:

			break;
		case EAIPawnState::EMove:

			break;
		case EAIPawnState::ENull:

			break;
	default:
		break;
	}
}

AActor* AAIPawn::BP_GetMoveTargetActor()
{
	return MoveTargetActor;
}

void AAIPawn::BP_SetMoveTargetActor(AActor* TargetActor)
{
	MoveTargetActor = TargetActor;
}

AActor* AAIPawn::BP_GetRotatorTargetActor()
{
	return RotatorTargetActor;
}

void AAIPawn::BP_SetRotatorTargetActor(AActor* TargetActor)
{
	RotatorTargetActor = TargetActor;
}
