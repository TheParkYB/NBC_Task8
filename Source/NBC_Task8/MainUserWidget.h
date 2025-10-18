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

protected:
	virtual void NativeConstruct() override;

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
	//일시정지 메뉴 활성화 여부
	void SetActivePauseMenu(bool pause);

private:
	//일시정지 버튼
	UFUNCTION()
	void OnClickPauseButton();
	
	//재개 버튼
	UFUNCTION()
	void OnClickResumeButton();

	//나가기 버튼
	UFUNCTION()
	void OnClickQuitButton();
	
	//웨이브 표기용 텍스트
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	class UTextBlock* waveTextBlock;

	//점수 표기용 텍스트
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* scoreTextBlock;

	//시간 표기용 텍스트
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* timeTextBlock;

	//일시정지 버튼
	UPROPERTY(EditAnywhere, Transient, meta = (AllowPrivateAccess = true, BindWidget))
	class UButton* pauseButton;

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

	//일시정지 메뉴
	UPROPERTY(EditAnywhere, Transient, meta = (AllowPrivateAccess = true, BindWidget))
	UWidget* pauseMenu;

	//재개 버튼
	UPROPERTY(EditAnywhere, Transient, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* resumeButton;

	//나가기 버튼
	UPROPERTY(EditAnywhere, Transient, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* quitButton;
};
