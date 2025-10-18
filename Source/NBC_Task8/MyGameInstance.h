#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

//게임 결과
enum class EGameResult
{
	None,
	GameOver,
	GameClear
};

UCLASS()
class NBC_TASK8_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	
	int GetScore() const;
	void SetScore(int value);

	EGameResult GetGameResult() const;
	void SetGameResult(EGameResult value);

	int GetStage() const;

	//게임 시작 (첫 번째 맵으로 이동)
	void GameStart();

	//다음 스테이지로 이동 (마지막 스테이지에서 실행하면 타이틀 맵으로)
	void GoToNextStage();

	//게임 오버
	void GameOver();

private:
	//점수
	int score;
	//게임 결과
	EGameResult gameResult;
	//스테이지 번호
	int stage;
	//맵 이름 목록
	TArray<FName> mapNames;
};
