// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/DecalComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialParameterCollection.h"
// Sets default values
AAIPawn::AAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

   this->InitComponent();

	bFaceActor.BindUObject(this,&AAIPawn::SetbFaceActor);
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
	//根据距离显示贴花
	TipLight();
	
	RotatorToActor(BP_GetRotatorTargetActor());
	
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
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//骨骼网格体
	Mesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetSkeletalMesh(LoadObject<USkeletalMesh>(NULL,TEXT("SkeletalMesh'/Game/GongPan_character/mask/mesh/mask3.mask3'")));
	Mesh->SetAnimClass(LoadClass<UAnimInstance>(NULL,TEXT("AnimBlueprint'/Game/BP/Piang/MianJuYingDao/Animation/BP_MaskAnimation.BP_MaskAnimation_C'")));
	Mesh->SetRelativeScale3D(FVector(0.3));
	Mesh->SetRelativeRotation(FRotator(0.0f,-90.0f,0.0f));
	
	Mesh2=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh2"));
	Mesh2->SetupAttachment(RootComponent);
	Mesh2->SetSkeletalMesh(LoadObject<USkeletalMesh>(NULL,TEXT("SkeletalMesh'/Game/GongPan_character/mask/mesh/mask3.mask3'")));
	Mesh2->SetAnimClass(LoadClass<UAnimInstance>(NULL,TEXT("AnimBlueprint'/Game/BP/Piang/MianJuYingDao/Animation/BP_MaskAnimation.BP_MaskAnimation_C'")));
	Mesh2->SetRelativeScale3D(FVector(0.3));
	Mesh2->SetRelativeRotation(FRotator(0.0f,-90.0f,0.0f));
	Mesh2->SetHiddenInGame(true);

	DeclLocation = CreateDefaultSubobject<USceneComponent>(TEXT("DeclLocation"));
	DeclLocation->SetupAttachment(Mesh);
	
	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->SetupAttachment(DeclLocation);
	DecalComp->SetVisibility(false);
	
	//MoveMent
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
}

void AAIPawn::RotatorToActor()
{
	if (RotatorTargetActor)
	{
		FVector StartPoint =  GetActorLocation();
		FVector EndPoint = BP_GetRotatorTargetActor()->GetActorLocation();

		//FRotator CurrentRotator = GetActorRotation();
		FRotator FaceRotator =  UKismetMathLibrary::FindLookAtRotation(StartPoint,EndPoint);

		//CurrentRotator = FMath::RInterpConstantTo(CurrentRotator,FaceRotator,GetWorld()->GetDeltaSeconds(),0.001f);
		SetActorRotation(FRotator(0.0f,FaceRotator.Yaw,0.0f));

		/*if (CurrentRotator.Equals(FaceRotator))
		{
			bComplete_Rotator.ExecuteIfBound(BP_GetMoveTargetActor());
			if (bComplete_Rotator.IsBound())
			{
				bComplete_Rotator.Unbind();
			}
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle_RotatorToActor);
		}*/
	}
}

void AAIPawn::RotatorToActor(AActor* Actor)
{
	BP_SetRotatorTargetActor(Actor);
	bool b=  bFaceActor.ExecuteIfBound(true);
	
	if (TimerHandle_RotatorToActor.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_RotatorToActor);
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_RotatorToActor,this,&AAIPawn::RotatorToActor,RotatorRate,true);
}

void AAIPawn::MoveToActor()
{
	if (Movement&&MoveTargetActor)
	{
		if (FVector::Distance(BP_GetMoveTargetActor()->GetActorLocation(),GetActorLocation())<100)
		{
			bComplete_Move.ExecuteIfBound(GetWorld()->GetFirstPlayerController());
			if (bComplete_Move.IsBound())
			{
				bComplete_Move.Unbind();
			}
			return;
		}else
		{
			bComplete_Move.ExecuteIfBound(BP_GetMoveTargetActor());
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), MoveTargetActor->GetActorLocation());
			return;
		}
		//Movement->AddInputVector(FRotator(0.0f,GetActorRotation().Yaw,0.0f).Vector(),false);
	}
}

void AAIPawn::MoveToActor(AActor* Actor)
{
	BP_SetMoveTargetActor(Actor);
	BP_SetRotatorTargetActor(Actor);
	if (TimerHandle_MoveToActor.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_MoveToActor);
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_MoveToActor,this,&AAIPawn::MoveToActor,MoveRate,true);
}

void AAIPawn::Talk_Implementation(AActor* TargetActor)
{
	MoveToActor(TargetActor);
	bComplete_Move.BindUObject(this,&AAIPawn::BP_SetRotatorTargetActorisPlayer);
}
void AAIPawn::Follow(AActor* TargetActor)
{
	MoveToActor(TargetActor);
	
	bComplete_Move.BindUObject(this,&AAIPawn::BP_SetRotatorTargetActorisPlayer);
}

void AAIPawn::WaitForPlayer(AActor* TargetActor)
{
	MoveToActor(TargetActor);
	bComplete_Move.BindUObject(this,&AAIPawn::BP_SetRotatorTargetActorisPlayer);
}

void AAIPawn::Delivery(AActor* TargetActor)
{
	if (TargetActor)
	{
		SetActorLocation(TargetActor->GetActorLocation());
	}
	Show();
}

void AAIPawn::NullState()
{
	bFaceActor.ExecuteIfBound(false);
	if (bComplete_Move.IsBound())
	{
		bComplete_Move.Unbind();
	}
	if (bComplete_Rotator.IsBound())
	{
		bComplete_Rotator.Unbind();
	}
	
	BP_SetMoveTargetActor(nullptr);
	BP_SetRotatorTargetActor(nullptr);
}

void AAIPawn::ChangeAIPawnState(EAIPawnState TargetState,AActor* MoveActor,AActor* RotatorActor)
{
	BP_SetMoveTargetActor(MoveActor);
	BP_SetRotatorTargetActor(RotatorActor);
	switch (TargetState)
	{
	case EAIPawnState::EFollow:
			Follow(MoveActor);
			break;
		case EAIPawnState::ETalk:
			Talk(MoveActor);
			break;
		case EAIPawnState::EWait:
			WaitForPlayer(MoveActor);
			break;
		case EAIPawnState::EMove:
			
			break;
		case EAIPawnState::EDelivery:
			Delivery(MoveActor);
			break;
		case EAIPawnState::ENull:
			NullState();
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

void AAIPawn::BP_SetRotatorTargetActorisPlayer(AActor* TargetActor)
{
	RotatorTargetActor = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void AAIPawn::SetbFaceActor(bool bFace)
{
	bFaceTargetActor = bFace;
}

void AAIPawn::Show()
{
	bTipLight = false;
	
	if (TimerHandle_Show.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Show);
	}
	if (!M_Mesh)
	{
		M_Mesh = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0),Mesh);
		
	}

	if (!M_Mesh2)
	{
		M_Mesh2 = UMaterialInstanceDynamic::Create(Mesh2->GetMaterial(0),Mesh2);
		
	}
	if (!MaterialParameterCollection)
	{
		MaterialParameterCollection=LoadObject<UMaterialParameterCollection>(NULL,TEXT("MaterialParameterCollection'/Game/Environment/Teleportation_VFX/diss.diss'"));
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Show,this,&AAIPawn::ShowTick,0.001f,true);
}

void AAIPawn::ShowTick()
{
	StartShow = FMath::FInterpTo(StartShow,EndShow,GetWorld()->GetDeltaSeconds(),ShowRate);
	/*if (M_Mesh&&M_Mesh2)
	{
		M_Mesh->SetScalarParameterValue(FName("Hight"),StartShow);
		M_Mesh2->SetScalarParameterValue(FName("Hight"),StartShow);
	}*/

	if (MaterialParameterCollection)
	{
		UKismetMaterialLibrary::SetScalarParameterValue(this,MaterialParameterCollection,FName("Hight"),StartShow);
	}
	if (FMath::IsNearlyEqual(StartShow,EndShow))
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Show);
		if (MaterialParameterCollection)
		{
			UKismetMaterialLibrary::SetScalarParameterValue(this,MaterialParameterCollection,FName("Hight"),ShowHight);
		}
		StartShow = -40.0f;
		bTipLight = true;
	}
}


void AAIPawn::TipLight()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_TipLight,this,&AAIPawn::TipLightTick,1.0f,true);
}

void AAIPawn::TipLightTick()
{
	if (!GetWorld()->GetFirstPlayerController()->GetPawn()||!DecalComp)
	{
		return;
	}
	if (bTipLight)
	{
		if (FVector::Distance(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(),GetActorLocation())<1000.0f)
		{
			
			DecalComp->SetVisibility(false);
			DecalComp->SetHiddenInGame(true);
		}else
		{
			DecalComp->SetVisibility(true);
			DecalComp->SetHiddenInGame(false);
			
		}
	}else
	{
		DecalComp->SetVisibility(false);
		DecalComp->SetHiddenInGame(true);
	}
}
