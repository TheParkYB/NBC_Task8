#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemManager.generated.h"

class AItemActor;

UCLASS()
class NBC_TASK8_API AItemManager : public AActor
{
	GENERATED_BODY()
	
public:
	static AItemManager* instance;
	static AItemManager* GetInstance();
	
	AItemManager();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void BeginDestroy() override;

	//아이템 효과 적용
	void InvokeItemEffect(int itemID);

	//아이템 생성
	void SpawnItems(int itemID, int spawnCount, bool addToAllItems = true);

	//아이템 제거
	void DeleteItem(AActor* target);

	//모든 아이템 제거 (allItems에 없는 아이템은 DeleteItem으로 제거)
	void DeleteAllItems();

private:
	//아이템 액터 목록
	UPROPERTY(EditInstanceOnly, Category = "Item Actor", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<AItemActor>> itemActors;

	//맵의 X방향 절반 길이
	UPROPERTY(EditInstanceOnly, Category = "Item Actor", meta = (AllowPrivateAccess = true))
	float halfLengthX;

	//맵의 Y방향 절반 길이
	UPROPERTY(EditInstanceOnly, Category = "Item Actor", meta = (AllowPrivateAccess = true))
	float halfLengthY;

	//캐릭터 액터
	UPROPERTY()
	class ANBC_Task8Character* playerCharacter = nullptr;
	
	//바닥과 아이템 사이의 거리
	const float ITEM_FROM_FLOOR = 100.0f;
	//아이템 생성시 아이템과 캐릭터의 최소 거리 (제곱 합)
	const float ITEM_FROM_PLAYER = 1000.0f;
	//동전 아이템의 점수
	const int COIN_SCORE = 100;

	//속도 감소 메세지
	const FString SPEED_DEBUFF_MSG = TEXT("이동 속도 감소");
	//이동 반전 메세지
	const FString REVERSE_MOVING_MSG = TEXT("이동 방향 반전");
	//회복 메세지
	const FString RESTORE_MSG = TEXT("디버프 해제");
	//장애물 속도 증가
	const FString OBSTACLE_ACCELERATION = TEXT("장애물 속도 증가");
	//장애물 속도 감소
	const FString OBSTACLE_DECELERATION = TEXT("장애물 속도 감소");
	//장애물 회전 방향 반전
	const FString OBSTACLE_CHANGE_DIRECTION = TEXT("장애물 회전 방향 변경");

	//맵에 존재하는 아이템 목록
	UPROPERTY()
	TSet<AActor*> allItems;
	
	//생성한 동전 아이템 개수
	int spawnCoinCount;
};
