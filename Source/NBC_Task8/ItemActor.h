#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

UCLASS()
class NBC_TASK8_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemActor();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	//캐릭터와 겹칠 때 실행
	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
		int otherBodyIndex, bool fromSweep, const FHitResult& sweepResult);
	
	//아이템 판정 범위
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	class USphereComponent* sphereCollider;

	//아이템의 스태틱 메시
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* itemMesh;

	//아이템 번호
	UPROPERTY(EditDefaultsOnly, Category="Item", meta = (AllowPrivateAccess=true))
	int itemID;

	//최소 회전 속도
	UPROPERTY(EditDefaultsOnly, Category="Item", meta = (AllowPrivateAccess=true))
	float minRotatingSpeed;

	//최대 회전 속도
	UPROPERTY(EditDefaultsOnly, Category="Item", meta = (AllowPrivateAccess=true))
	float maxRotatingSpeed;

	//정해진 회전 속도
	FRotator rotatingValue;
};
