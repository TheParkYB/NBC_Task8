#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUserWidget.generated.h"

//웨이브 종류
enum class EWaveType
{
	Normal,
	Skull,
	Ice
};

UCLASS()
class NBC_TASK8_API UMainUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//웨이브
	void SetWave(int wave);
	//점수
	void SetScore(int score);
	//남은 시간
	void SetRemainingTime(int remainingTime);
	//웨이브 알림
	void WaveAlert(EWaveType wave);
	//하단 메세지 출력
	void ShowBottomMessage(FString message, FColor textColor);

private:
	//웨이브 표기용 텍스트
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	class UTextBlock* waveTextBlock;

	//점수 표기용 텍스트
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* scoreTextBlock;

	//시간 표기용 텍스트
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* timeTextBlock;

	//하단 메세지 텍스트
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* messageTextBlock;

	//일반 웨이브 알림
	UPROPERTY(EditAnywhere, Transient, meta = (AllowPrivateAccess = true, BindWidgetAnim))
	UWidgetAnimation* normalWaveAnimation;

	//해골 웨이브 알림
	UPROPERTY(EditAnywhere, Transient, meta = (AllowPrivateAccess = true, BindWidgetAnim))
	UWidgetAnimation* skullWaveAnimation;

	//얼음 웨이브 알림
	UPROPERTY(EditAnywhere, Transient, meta = (AllowPrivateAccess = true, BindWidgetAnim))
	UWidgetAnimation* iceWaveAnimation;

	//하단 메세지 알림
	UPROPERTY(EditAnywhere, Transient, meta = (AllowPrivateAccess = true, BindWidgetAnim))
	UWidgetAnimation* bottomMessage;
};
