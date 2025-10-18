#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameState.generated.h"

UCLASS()
class NBC_TASK8_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:
	//유저 위젯 추가가 완료된 직후에 실행하는 함수
	void AfterAddWidgetToViewport();
	
	//다음 웨이브 진행
	void NextWave();

	//점수 추가
	void AddScore(int addValue);

private:
	//흘러가는 제한 시간
	void TimeLimitCounting();
	
	//웨이브 시작시 생성하는 동전 아이템 개수
	const int START_COIN_COUNT = 12;

	//웨이브 * 이 변수 만큼 추가 코인 생성
	const int EXTRA_COIN_MEASURE = 3;

	//2번째 웨이브에서 생성하는 해골, 구급약 아이템 개수
	const int SUB_ITEM_COUNT = 5;

	//웨이브당 제한 시간 (초)
	const int TIME_LIMIT_SECOND = 60;

	//제한 시간을 세는 단위 (초)
	const float TIME_LIMIT_COUNT_AMOUNT = 0.1f;

	//플레이어 컨트롤러
	UPROPERTY()
	class AMyPlayerController* playerController;

	//게임 인스턴스
	UPROPERTY()
	class UMyGameInstance* myGameInstance;

	//제한 시간용 핸들
	FTimerHandle timerHandle;
	
	//현재 웨이브
	int currentWave = 0;

	//점수
	int score = 0;

	//현재 남은 시간
	int remainingTime = 0;

	//1초를 세기 위한 변수
	float timeCounting = 0;
};
