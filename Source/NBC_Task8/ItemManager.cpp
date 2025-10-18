#include "ItemManager.h"
#include "ItemActor.h"
#include "MainUserWidget.h"
#include "MyGameState.h"
#include "MyPlayerController.h"
#include "NBC_Task8Character.h"
#include "RotatingObstacle.h"

AItemManager* AItemManager::instance = nullptr;
AItemManager* AItemManager::GetInstance()
{
	return instance;
}

AItemManager::AItemManager()
{
	PrimaryActorTick.bCanEverTick = true;
	spawnCoinCount = 0;
}

void AItemManager::BeginPlay()
{
	Super::BeginPlay();
	playerCharacter = Cast<ANBC_Task8Character>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void AItemManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	instance = this;
}

void AItemManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemManager::BeginDestroy()
{
	Super::BeginDestroy();
	instance = nullptr;
}

void AItemManager::InvokeItemEffect(int itemID)
{
	switch (itemID)
	{
	case 1://동전
		{
			AMyGameState* gameState = Cast<AMyGameState>(GetWorld()->GetGameState());
			if (gameState != nullptr)
			{
				//점수 추가
				gameState->AddScore(COIN_SCORE);
				//모든 동전 획득시 다음 웨이브
				if (--spawnCoinCount == 0)
					gameState->NextWave();
			}
		}
		break;
		
	case 2://해골
		{
			FString message;
			if (FMath::RandRange(0, 1) == 0)
			{
				//이동 속도 감소
				playerCharacter->SpeedDebuff();
				message = SPEED_DEBUFF_MSG;
			}
			else
			{
				//이동 반전
				playerCharacter->ReverseMovingDebuff();
				message = REVERSE_MOVING_MSG;
			}
			
			//메세지
			if (AMyPlayerController* controller = Cast<AMyPlayerController>(playerCharacter->GetController()); controller != nullptr)
				controller->GetUserWidget()->ShowBottomMessage(message, FColor::Purple);
		}
		break;
		
	case 3://구급약
		{
			playerCharacter->RestoreMovement();

			//메세지
			if (AMyPlayerController* controller = Cast<AMyPlayerController>(playerCharacter->GetController()); controller != nullptr)
				controller->GetUserWidget()->ShowBottomMessage(RESTORE_MSG, FColor::Green);
		}
		break;

	//스테이지3의 장애물 관련 아이템
	case 4://속도 증가
	case 5://속도 감소
	case 6://방향 변경
		{
			ARotatingObstacle* rotatingObstacle = ARotatingObstacle::GetInstance();
			if (!::IsValid(rotatingObstacle))
				break;

			AMyPlayerController* controller = Cast<AMyPlayerController>(playerCharacter->GetController());
			if (controller == nullptr)
				return;
	
			if (itemID == 6)//방향 변경
			{
				rotatingObstacle->ChangeRotatingDirection();
				controller->GetUserWidget()->ShowBottomMessage(OBSTACLE_CHANGE_DIRECTION, FColor::White);
			}
			else//속도 증감
			{
				bool acceleration = itemID == 4;
				rotatingObstacle->AccelerateOrDecelerate(acceleration);
				controller->GetUserWidget()->ShowBottomMessage(acceleration ? OBSTACLE_ACCELERATION : OBSTACLE_DECELERATION, FColor::White);
			}
				
			//적용한 아이템 재생성
			SpawnItems(itemID, 1, false);
		}
		break;
		
	default:
		break;
	}
}

void AItemManager::SpawnItems(int itemID, int spawnCount, bool addToAllItems)
{
	//1개 이상 생성
	if (spawnCount <= 0)
		return;
	
	//제대로된 아이템 번호 필요 (1부터 시작)
	if (!itemActors.IsValidIndex(itemID - 1))
		return;
	
	//생성할 아이템 종류
	TSubclassOf<AItemActor> makingItem = itemActors[itemID - 1];

	//현재 캐릭터 위치
	FVector curCharPos = playerCharacter->GetActorLocation();
	
	for (int iNum = 0; iNum < spawnCount; ++iNum)
	{
		//무작위 위치 (캐릭터와 너무 가까운 곳에서 생성하면 안됨)
		FVector spawnPoint;
		do
		{
			float x = FMath::RandRange(-halfLengthX, halfLengthX);
			float y = FMath::RandRange(-halfLengthY, halfLengthY);
			spawnPoint = FVector(x, y, ITEM_FROM_FLOOR);
		} while (FVector::DistSquared(spawnPoint, curCharPos) < ITEM_FROM_PLAYER);

		//해당 위치에 아이템을 생성
		AActor* spawnedItem = GetWorld()->SpawnActor<AItemActor>(makingItem, spawnPoint, FRotator::ZeroRotator);
		//allItems에 추가
		if (addToAllItems)
			allItems.Add(spawnedItem);
	}

	//동전 아이템 추가시 개수 증가
	if (itemID == 1)
		spawnCoinCount += spawnCount;
}

void AItemManager::DeleteItem(AActor* target)
{
	//올바른 아이템을 지젇해야 함
	if (!::IsValid(target))
		return;

	//allItems에 있을 경우 제거
	allItems.Remove(target);
	//아이템 제거
	GetWorld()->DestroyActor(target);
}

void AItemManager::DeleteAllItems()
{
	//allItems에 모든 아이템을 맵에서 삭제
	for (AActor* item : allItems)
	{
		if (!::IsValid(item))
			continue;

		GetWorld()->DestroyActor(item);
	}

	//마지막으로 allItems도 비운다.
	allItems.Empty();
}
