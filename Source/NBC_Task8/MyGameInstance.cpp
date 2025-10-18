#include "MyGameInstance.h"

#include "Kismet/GameplayStatics.h"

void UMyGameInstance::Init()
{
	Super::Init();

	score = 0;
	gameResult = EGameResult::None;
	stage = 0;
	mapNames = { TEXT("Title"), TEXT("Stage1"), TEXT("Stage2"), TEXT("Stage3") };
}

int UMyGameInstance::GetScore() const
{
	return score;
}

void UMyGameInstance::SetScore(int value)
{
	score = value;
}

EGameResult UMyGameInstance::GetGameResult() const
{
	return gameResult;
}

void UMyGameInstance::SetGameResult(EGameResult value)
{
	gameResult = value;
}

int UMyGameInstance::GetStage() const
{
	return stage;
}

void UMyGameInstance::GameStart()
{
	//게임 진행 내용 초기화
	score = 0;
	gameResult = EGameResult::None;
	//1번째 맵
	stage = 1;
	UGameplayStatics::OpenLevel(GetWorld(), mapNames[stage]);
}

void UMyGameInstance::GoToNextStage()
{
	//이 if문에 들어간다면 게임 클리어
	if (!mapNames.IsValidIndex(++stage))
	{
		gameResult = EGameResult::GameClear;
		stage = 0;
	}
		
	UGameplayStatics::OpenLevel(GetWorld(), mapNames[stage]);
}

void UMyGameInstance::GameOver()
{
	gameResult = EGameResult::GameOver;
	stage = 0;
	UGameplayStatics::OpenLevel(GetWorld(), mapNames[stage]);
}

void UMyGameInstance::StopGame()
{
	gameResult = EGameResult::None;
	stage = 0;
	UGameplayStatics::OpenLevel(GetWorld(), mapNames[stage]);
}
