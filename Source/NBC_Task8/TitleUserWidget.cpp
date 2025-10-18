#include "TitleUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyGameInstance.h"
#include "Components/TextBlock.h"

void UTitleUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//버튼 클릭 이벤트
	startButton->OnClicked.AddDynamic(this, &UTitleUserWidget::OnClickStartButton);
	exitButton->OnClicked.AddDynamic(this, &UTitleUserWidget::OnClickExitButton);
	
	//필요한 위젯만 사용하기
	UMyGameInstance* myGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	EGameResult gameResult = myGameInstance->GetGameResult();
	//상단 텍스트
	titleText->SetVisibility(gameResult == EGameResult::None ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	gameOverText->SetVisibility(gameResult == EGameResult::GameOver ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	gameClearText->SetVisibility(gameResult == EGameResult::GameClear ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	//점수
	if (gameResult == EGameResult::None)
	{
		scoreBox->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		scoreBox->SetVisibility(ESlateVisibility::Visible);
		FString scoreString = FString::Printf(TEXT("%d"), myGameInstance->GetScore());
		scoreText->SetText(FText::FromString(scoreString));
	}
}

void UTitleUserWidget::OnClickStartButton()
{
	UMyGameInstance* myGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	myGameInstance->GameStart();
}

void UTitleUserWidget::OnClickExitButton()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}