#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingObstacle.generated.h"

UCLASS()
class NBC_TASK8_API ARotatingObstacle : public AActor
{
	GENERATED_BODY()

public:
	static ARotatingObstacle* instance;
	static ARotatingObstacle* GetInstance();
	
	ARotatingObstacle();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void BeginDestroy() override;

	//회전 속도 증감
	void AccelerateOrDecelerate(bool acceleration);

	//회전 방향 변경
	void ChangeRotatingDirection();

private:
	//회전 속도
	UPROPERTY(EditAnywhere, Category = "Rotation Settings", meta = (AllowPrivateAccess = "true"))
	float rotatingSpeed;

	//최소 회전 속도
	UPROPERTY(EditAnywhere, Category = "Rotation Settings", meta = (AllowPrivateAccess = "true"))
	float minSpeed;

	//최대 회전 속도
	UPROPERTY(EditAnywhere, Category = "Rotation Settings", meta = (AllowPrivateAccess = "true"))
	float maxSpeed;

	//속도 증감시 단위 값
	UPROPERTY(EditAnywhere, Category = "Rotation Settings", meta = (AllowPrivateAccess = "true"))
	float accelerationMeasure;

	//반시계 여부
	UPROPERTY(EditAnywhere, Category = "Rotation Settings", meta = (AllowPrivateAccess = "true"))
	bool antiClock;

	//회전 속도에 의해 정해진 회전 값
	FRotator rotationValue;
};

inline void ARotatingObstacle::BeginDestroy()
{
	Super::BeginDestroy();

	instance = nullptr;
}
