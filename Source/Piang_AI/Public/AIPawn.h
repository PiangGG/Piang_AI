// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

UENUM()
enum class EAIPawnState:uint8
{
	//AI状态
	EFollow UMETA(DisplayName = "跟随"),
	
	ETalk UMETA(DisplayName = "交谈"),
	
	EWait UMETA(DisplayName = "等待"),
	
	EMove UMETA(DisplayName = "移动并转向"),
	
	ENull UMETA(DisplayName = "无"),
};

UCLASS()
class PIANG_AI_API AAIPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/*
	 * All Var
	 */
	//当前状态
	EAIPawnState CurrentAIPawnState;

	//转向Actor
	FTimerHandle TimerHandle_RotatorToActor;
	//是否始终面向Actor
	bool bFaceTargetActor = false;
	AActor *TargetActor = nullptr;

	//移动向Actor
	FTimerHandle TimerHandle_MoveToActor;

	//
	FVector FollowLocation = FVector(0,-300,0);
	
	FVector TalkLocation = FVector(0,300,100);
public:
	/**
	 * All Component
	 */

	//骨骼网格体
	class USkeletalMeshComponent* Mesh;
	//移动 Movement
	class UFloatingPawnMovement* Movement;

	//Init All Component
	virtual void InitComponent();

	
	/*
	 * Operctor
	 */
	void RotatorToActor();//
	void RotatorToActor(AActor* TargetActor);//直接旋转到位置
	void RotatorToActor(AActor* TargetActor,float RotatorRate = 0.001);

	void MoveToActor();
	void MoveToActor(AActor* TargetActor,float RotatorRate = 0.001);
	void MoveToLocation(FVector TargetVector,float RotatorRate = 0.001);

	void ChangeAiPawnState(EAIPawnState TargetState);

	AActor* GetTargetActor();
	void SetTargetActor(AActor* TargetActor);
};
