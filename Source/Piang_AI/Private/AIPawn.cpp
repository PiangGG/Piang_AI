// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"

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

}

// Called to bind functionality to input
void AAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIPawn::InitComponent()
{
	//骨骼网格体
	Mesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	//Mesh->SetSkeletalMesh(LoadObject<USkeletalMesh>(NULL,TEXT("")));
	//Mesh->SetAnimClass(LoadClass<UAnimInstance>(NULL,TEXT("")));

	//MoveMent
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
}

void AAIPawn::RotatorToActor()
{
	if (TargetActor)
	{
		FVector StartPoint =  GetActorLocation();
		FVector EndPoint = TargetActor->GetActorLocation();

		FRotator CurrentRotator = GetActorRotation();
		FRotator FaceRotator =  UKismetMathLibrary::FindLookAtRotation(StartPoint,EndPoint);

		CurrentRotator = FMath::RInterpConstantTo(CurrentRotator,FaceRotator,GetWorld()->GetDeltaSeconds(),1.0f);
		SetActorRotation(CurrentRotator);
	}
}

void AAIPawn::RotatorToActor(AActor* TargetActor)
{
	FVector StartPoint =  GetActorLocation();
	FVector EndPoint = TargetActor->GetActorLocation();
	FRotator FaceRotator =  UKismetMathLibrary::FindLookAtRotation(StartPoint,EndPoint);
	SetActorRotation(FaceRotator);
}

void AAIPawn::RotatorToActor(AActor* TargetActor,float RotatorRate)
{
	SetTargetActor(TargetActor);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_RotatorToActor,this,&AAIPawn::RotatorToActor,RotatorRate,true);
}

void AAIPawn::MoveToActor()
{
	if (Movement&&TargetActor)
	{
		if (FVector::Distance(GetTargetActor()->GetActorLocation(),GetActorLocation())<100)
		{
			return;
		}
		Movement->AddInputVector(FRotator(0.0f,GetActorRotation().Yaw,0.0f).Vector(),false);
	}
}

void AAIPawn::MoveToActor(AActor* TargetActor,float MoveRate)
{
	SetTargetActor(TargetActor);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_MoveToActor,this,&AAIPawn::MoveToActor,MoveRate,true);
}

void AAIPawn::MoveToLocation(FVector TargetVector, float RotatorRate)
{
	
}

void AAIPawn::ChangeAiPawnState(EAIPawnState TargetState)
{
	switch (TargetState)
	{
		case EAIPawnState::EFollow:
			//MoveToLocation();
			break;
		case EAIPawnState::ETalk:
			
			break;
		
		case EAIPawnState::EWait:

			break;
		case EAIPawnState::EMove:

			break;
		case EAIPawnState::ENull:

			break;
	default: ;
	}
}

AActor* AAIPawn::GetTargetActor()
{
	return TargetActor;
}

void AAIPawn::SetTargetActor(AActor* TargetActor)
{
	this->TargetActor = TargetActor;
}
