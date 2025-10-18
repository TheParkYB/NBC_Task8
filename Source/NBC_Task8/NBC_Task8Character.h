// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "NBC_Task8Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ANBC_Task8Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	//일시정지 입력 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* pauseAction;

	//스테이지 스킵 액션 (에디터용)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* stageSkipAction;

public:
	ANBC_Task8Character();
	

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			
	//일시정지 입력으로 호출되는 함수
	void Pause(const FInputActionValue& value);

	//스테이지 스팁 입력으로 호출되는 함수
	void StageSkip(const FInputActionValue& value);
	
protected:

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	//속도 디버프
	void SpeedDebuff();

	//이동 방향 디버프
	void ReverseMovingDebuff();

	//이동 디버프 제거
	void RestoreMovement();

	//제동력과 마찰값 감소
	void SlipperyFloor();

	//제동력과 마찰값 복구
	void UnslipperyFloor();

private:
	//기본 이동 속도
	const float DEFAULT_MOVE_SPEED = 1000.0f;
	//기본 마찰값
	const float DEFAULT_MOVE_FRICTION = 8.0f;
	//기본 제동력
	const float DEFAULT_MOVE_DECELERATION = 3000.0f;
	
	//디버프애 의한 최저 속도
	const float MIN_MOVE_SPEED = 300.0f;

	//얼음 바닥의 마찰값
	const float ICE_MOVE_FRICTION = 1.0f;
	//얼음 바닥의 제동력
	const float ICE_MOVE_DECELERATION = 100.0f;

	//반대방향으로 이동
	bool reverseMoving = false;
};

