#include "RotatingObstacle.h"

ARotatingObstacle* ARotatingObstacle::instance = nullptr;
ARotatingObstacle* ARotatingObstacle::GetInstance()
{
	return instance;
}

ARotatingObstacle::ARotatingObstacle()
{
	PrimaryActorTick.bCanEverTick = true;
	rotationValue = FRotator();
	antiClock = false;
}

void ARotatingObstacle::BeginPlay()
{
	Super::BeginPlay();
	rotationValue = FRotator(0, rotatingSpeed, 0);
	if (antiClock)
		rotationValue *= -1;
}

void ARotatingObstacle::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	instance = this;
}

void ARotatingObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldRotation(rotationValue * DeltaTime);
}

void ARotatingObstacle::AccelerateOrDecelerate(bool acceleration)
{
	rotatingSpeed += acceleration ? accelerationMeasure : -accelerationMeasure;
	if (rotatingSpeed > maxSpeed)
		rotatingSpeed = maxSpeed;
	else if (rotatingSpeed < minSpeed)
		rotatingSpeed = minSpeed;
	
	rotationValue = FRotator(0, rotatingSpeed, 0);
	if (antiClock)
		rotationValue *= -1;
}

void ARotatingObstacle::ChangeRotatingDirection()
{
	antiClock = !antiClock;
	rotationValue *= -1;
}