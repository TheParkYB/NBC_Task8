#include "MainUserWidget.h"
#include "Components/TextBlock.h"

void UMainUserWidget::SetWave(int wave)
{
	if (waveTextBlock == nullptr)
		return;
	
	FString waveString = FString::Printf(TEXT("Wave %d"), wave);
	waveTextBlock->SetText(FText::FromString(waveString));
}

void UMainUserWidget::SetScore(int score)
{
	if (scoreTextBlock == nullptr)
		return;
	
	FString scoreString = FString::Printf(TEXT("%d"), score);
	scoreTextBlock->SetText(FText::FromString(scoreString));
}

void UMainUserWidget::SetRemainingTime(int remainingTime)
{
	if (timeTextBlock == nullptr)
		return;

	FString remainingString = FString::Printf(TEXT("Time : %d"), remainingTime);
	timeTextBlock->SetText(FText::FromString(remainingString));

	//남은 시간 10초 기준으로 색깔 변경
	if (remainingTime <= 10)
		timeTextBlock->SetColorAndOpacity(FColor::Red);
	else
		timeTextBlock->SetColorAndOpacity(FColor::Green);
}

void UMainUserWidget::WaveAlert(EWaveType wave)
{
	//주어진 값에 맞는 애니메이션을 실행한다.
	switch (wave)
	{
	case EWaveType::Normal:
		PlayAnimation(normalWaveAnimation);
		break;

	case EWaveType::Skull:
		PlayAnimation(skullWaveAnimation);
		break;

	case EWaveType::Ice:
		PlayAnimation(iceWaveAnimation);
		break;

	default:
		break;
	}
}

void UMainUserWidget::ShowBottomMessage(FString message, FColor textColor)
{
	if (bottomMessage == nullptr)
		return;

	//텍스트 블록
	messageTextBlock->SetText(FText::FromString(message));
	messageTextBlock->SetColorAndOpacity(textColor);

	//연출
	PlayAnimation(bottomMessage);
}
