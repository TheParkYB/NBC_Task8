#include "MyPlayerController.h"
#include "MainUserWidget.h"
#include "MyGameState.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//위젯
	if (mainUserWidget != nullptr)
	{
		mainUserWidget->AddToViewport();
		Cast<AMyGameState>(GetWorld()->GetGameState())->AfterAddWidgetToViewport();
	}

	//마우스 커서
	SetShowMouseCursor(false);
}

bool AMyPlayerController::SetPause(bool bPause, FCanUnpause CanUnpauseDelegate)
{
	//마우스 커서
	SetShowMouseCursor(bPause);
	//메뉴
	mainUserWidget->SetActivePauseMenu(bPause);
	
	return Super::SetPause(bPause,CanUnpauseDelegate);
}

UMainUserWidget* AMyPlayerController::GetUserWidget()
{
	return mainUserWidget;
}
