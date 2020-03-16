// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonBase.generated.h"



UENUM(BlueprintType)
enum class EButtonType : uint8
{
	BT_TargetChanger UMETA(DisplayName = "TargetsChanger")

	,BT_Freezer UMETA(DisplayName = "Freezer")

	,BT_Speeder UMETA(DisplayName = "Speeder")

	,BT_Collaborative UMETA(DisplayName = "Collaborative")

	,BT_TypeChanger UMETA(DisplayName = "Type Changer")

	,BT_None UMETA(DisplayName = None)


};


//FWD Declarations

class AMovingPlatformBase;
class UBoxComponent;
class ATargetPointBase;


UCLASS()
class PLATFORMGAME_API AButtonBase : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AButtonBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//GETTERS


	UFUNCTION(BlueprintPure , Category = "ButtonBase")
	EButtonType GetButtonType();




	UFUNCTION(BlueprintCallable, Category = "ButtonBase")
		void ApplyEffect();


	UFUNCTION(BlueprintCallable, Category = "ButtonBase")
		void UnapplyEffect();


	UFUNCTION(BlueprintCallable , Category = "EffectButton")
		void ApplyFreezeToPlatform(bool bNewPlatformState );


	UFUNCTION(BlueprintCallable, Category = "EffectButton")
		void UnfreezePlatform();


	UFUNCTION(BlueprintCallable, Category = "EffectButton")
		void ApplySpeedToPlatform(float fNewSpeed);
	

	UFUNCTION(BlueprintCallable, Category = "EffectButton")
		void UnapplySpeedToPlatform();


	UFUNCTION(BlueprintCallable, Category = "EffectButton")
		void ChangeTargetsToPlatform();


	UFUNCTION(BlueprintCallable, Category = "EffectButton")
		void UnchangeTargetsToPlatform();





	//PROPERTIES

protected:

	UPROPERTY(EditAnywhere, Category = "ButtonBase")
		EButtonType ButtonMainType = EButtonType::BT_TargetChanger ;

	UPROPERTY(EditAnywhere, Category = "ButtonBase")
		EButtonType SecundaryButtonType = EButtonType::BT_None;

	//ThePlatform the Button is going to interact with.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonBase")
	AMovingPlatformBase* MovingPlatformToInteract;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;

	/*Targets that the platform will reach on activation*/
	UPROPERTY(EditAnywhere, Category = "ButtonBase")
	TArray<ATargetPointBase*> TargetsToReachOnActivation;

	/*If true the current button just affects the platform if the player is on top of it.
	  If Has Timer is activated, it will be automatically desactivated.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly , Category = "ButtonBase" , meta = (DisplayName = "IsPositionOnly"))
	bool bIsPositionOnly;

	/*Determines whether the button has a timer which deactivates the function activated when pushed the button*/
	UPROPERTY(EditAnywhere , BlueprintReadOnly,  Category = "ButtonBase" , meta=(DisplayName ="HasTimer"))
	bool bHasTimer;

	/*Time that the activated function by the button will last (if HasTimer is true) */
	UPROPERTY(EditAnywhere , Category = "ButtonBase" , meta = (DisplayName = "DeactivationTime"))
	float fActivatedTime;

	UPROPERTY(BlueprintReadOnly , Category = "ButtonBase" , meta = (DisplayName = "IsButtonActive"))
	bool bIsButtonActive;



	UPROPERTY(EditAnywhere, Category = "ButtonEffect")
	float fSpeedToAdd UMETA(DisplayName = "SpeedToAdd");
	

	

	


	FTimerHandle TimeHandle;

	FTimerHandle EffectTimer;

	//FUNCTIONS

/*	Event That is Trigger when the effect timer has reached to the end, if the button has one.*/
	UFUNCTION(BlueprintImplementableEvent , meta = (DisplayName = "On Timer Finish"))
	void OnTimerFinish();







	void OnPushButton();

	void OnUnpushButton();

	void AddTargetsToReachOnActivationToPlatformArray(TArray<ATargetPointBase*> TargetPoints);

	void ActiveButton(bool bButtonState);

	void DesactiveButton(bool bButtonState);




	//DELEGATES


		UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		UFUNCTION()
		void OnComponentEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};

