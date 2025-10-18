#include "MyGameState.h"
#include "ItemManager.h"
#include "MyPlayerController.h"
#include "MainUserWidget.h"
#include "MyGameInstance.h"
#include "NBC_Task8Character.h"
#include "Kismet/GameplayStatics.h"

void AMyGameState::BeginPlay()
{
	Super::BeginPlay();

	playerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (playerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController is null"));
		return;
	}

	score = myGameInstance->GetScore();
	currentWave = 0;
}

void AMyGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	myGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (myGameInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MyGameInstance is null"));
	}
}

void AMyGameState::AfterAddWidgetToViewport()
{
	NextWave();

	//3스테이지 한정 아이템 생성
	if (myGameInstance->GetStage() == 3)
	{
		AItemManager::GetInstance()->SpawnItems(4, 1, false);
		AItemManager::GetInstance()->SpawnItems(5, 1, false);
		AItemManager::GetInstance()->SpawnItems(6, 1, false);
	}

	//제한 시간 적용 시작
	GetWorldTimerManager().SetTimer(timerHandle, this, &AMyGameState::TimeLimitCounting , TIME_LIMIT_COUNT_AMOUNT, true);
}

void AMyGameState::NextWave()
{
	//웨이브 증가
	++currentWave;

	//남은 제한 시간 만큼 점수 증가
	AddScore(remainingTime);

	//4웨이브로 확인되면 다음 맵으로 이동
	if (currentWave >= 4)
	{
		myGameInstance->SetScore(score);
		myGameInstance->GoToNextStage();
		return;
	}

	//UI 반영
	UMainUserWidget* widget = playerController->GetUserWidget();
	widget->SetWave(currentWave);

	//맵에 남아있는 모든 아이템 제거
	AItemManager::GetInstance()->DeleteAllItems();

	//동전 아이템 생성
	AItemManager::GetInstance()->SpawnItems(1, START_COIN_COUNT);

	//일반 웨이브 알림
	if (currentWave == 1)
		widget->WaveAlert(EWaveType::Normal);
	
	//2번째 웨이브에서 해골, 구급약 아이템 생성
	if (currentWave == 2)
	{
		AItemManager::GetInstance()->SpawnItems(2, SUB_ITEM_COUNT);
		AItemManager::GetInstance()->SpawnItems(3, SUB_ITEM_COUNT);

		//해골 웨이브 알림
		widget->WaveAlert(EWaveType::Skull);
	}
	
	//3번째 웨이브에서 바닥이 미끄러움
	ANBC_Task8Character* player = Cast<ANBC_Task8Character>(playerController->GetCharacter());
	if (currentWave == 3)
	{
		player->SlipperyFloor();
		widget->WaveAlert(EWaveType::Ice);//얼름 웨이브 알림
	}
	else
	{
		player->UnslipperyFloor();
	}
	
	//제한 시간 초기화
	remainingTime = TIME_LIMIT_SECOND;
	timeCounting = 0;
	widget->SetRemainingTime(remainingTime);
}

void AMyGameState::AddScore(int addValue)
{
	score += addValue;
	//UI 반영
	UMainUserWidget* widget = playerController->GetUserWidget();
	widget->SetScore(score);
}

void AMyGameState::TimeLimitCounting()
{
	timeCounting += TIME_LIMIT_COUNT_AMOUNT;

	//1초마다 시간 감소 적용
	if (timeCounting >= 1.0f)
	{
		timeCounting -= 1.0f;
		remainingTime--;

		//UI에 반영
		UMainUserWidget* widget = playerController->GetUserWidget();
		widget->SetRemainingTime(remainingTime);
		
		//0초 도달시 게임 종료
		if (remainingTime == 0)
		{
			myGameInstance->SetScore(score);
			myGameInstance->GameOver();
		}
	}
}