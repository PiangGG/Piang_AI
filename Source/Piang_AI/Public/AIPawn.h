// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "../../../../ZMY_Interaction/Source/ZMY_Interaction/Public/Component/DialogueComponent.h"
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

	EDelivery UMETA(DisplayName = "传送"),
	
	ENull UMETA(DisplayName = "无"),
};

DECLARE_DELEGATE_OneParam(bCompleteDelegate,AActor*);
DECLARE_DELEGATE_OneParam(bFaceActorDelegate,bool);
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
	//始终面向TargetActor
	bFaceActorDelegate bFaceActor;
	
	//移动向Actor
	FTimerHandle TimerHandle_MoveToActor;

	UPROPERTY(VisibleAnywhere)
	FVector FollowLocation = FVector(0,-300,0);

	UPROPERTY(VisibleAnywhere)
	FVector TalkLocation = FVector(0,300,100);

	//完成的委托
	bCompleteDelegate bComplete_Move;
	
	bCompleteDelegate bComplete_Rotator;
public:
	/**
	 * All Component
	 */

	//骨骼网格体
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Mesh;
	UMaterialInstanceDynamic* M_Mesh;
	
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Mesh2;
	UMaterialInstanceDynamic* M_Mesh2;
	
	//移动 Movement
	UPROPERTY(VisibleAnywhere)
	class UFloatingPawnMovement* Movement;
	//对话组件
	// UPROPERTY(VisibleAnywhere)
	// class UDialogueComponent* DialogueComponent;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* DeclLocation;
	
	UPROPERTY(VisibleAnywhere)
	class UDecalComponent* DecalComp;
	
	//Init All Component
	virtual void InitComponent();

	
	/*
	 * Operctor
	 */
	UPROPERTY(VisibleAnywhere)
	bool bCanOperctor = true;
	//转向目标
	void RotatorToActor();//
	UFUNCTION(BlueprintCallable)
	void RotatorToActor(AActor* TargetActor);
	UPROPERTY(VisibleAnywhere)
	float RotatorRate = 0.001f;
	
	//移动向目标
	void MoveToActor();
	UFUNCTION(BlueprintCallable)
	void MoveToActor(AActor* TargetActor);
	UPROPERTY(VisibleAnywhere)
	float MoveRate = 1.0f;

	//交谈
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Talk(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable)
	void Follow(AActor* TargetActor);
	
	//等待
	UFUNCTION(BlueprintCallable)
	void WaitForPlayer(AActor* TargetActor);

	//传送到目标
	UFUNCTION(BlueprintCallable)
	void Delivery(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void NullState();

	
	UFUNCTION(BlueprintCallable)
	void ChangeAIPawnState(EAIPawnState TargetState,AActor* MoveActor,AActor* RotatorActor);

	UFUNCTION(BlueprintCallable)
	AActor* BP_GetMoveTargetActor();
	UFUNCTION(BlueprintCallable)
	void BP_SetMoveTargetActor(AActor* TargetActor);

	UPROPERTY()
	AActor *MoveTargetActor = nullptr;

	UFUNCTION(BlueprintCallable)
	AActor* BP_GetRotatorTargetActor();
	UFUNCTION(BlueprintCallable)
	void BP_SetRotatorTargetActor(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void BP_SetRotatorTargetActorisPlayer(AActor* TargetActor);
	
	UPROPERTY()
	AActor *RotatorTargetActor = nullptr;

	//设置是否始终面向Actor
	UFUNCTION(BlueprintCallable)
	void SetbFaceActor(bool bFace);

	//显示
	UFUNCTION()
	void Show();

	UPROPERTY()
	class UMaterialParameterCollection* MaterialParameterCollection;
	
	UFUNCTION()
	void ShowTick();
	UPROPERTY(VisibleAnywhere)
	float ShowHight = -800;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	float StartShow = -40.0f;
	float EndShow = -80.0f;
	UPROPERTY(VisibleAnywhere,Category=Show)
	float ShowRate = 1;
	UPROPERTY(VisibleAnywhere,Category=Show)
	FTimerHandle TimerHandle_Show;



	/*
	 * TipLight
	 */
	void TipLight();
	void TipLightTick();
	UPROPERTY(VisibleAnywhere,Category=TipLight)
	FTimerHandle TimerHandle_TipLight;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool bTipLight = true;
};



