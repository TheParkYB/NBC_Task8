#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleUserWidget.generated.h"

UCLASS()
class NBC_TASK8_API UTitleUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	//시작 버튼 클릭
	UFUNCTION()
	void OnClickStartButton();
	
	//종료 버튼 클릭
	UFUNCTION()
	void OnClickExitButton();
	
	//시작 버튼
	UPROPERTY(EditAnywhere, meta = (allowPrivateAccess = true, BindWidget))
	class UButton* startButton;

	//종료 버튼
	UPROPERTY(EditAnywhere, meta = (allowPrivateAccess = true, BindWidget))
	UButton* exitButton;

	//게임 타이틀 텍스트
	UPROPERTY(EditAnywhere, meta = (allowPrivateAccess = true, BindWidget))
	UWidget* titleText;

	//게임 오버 텍스트
	UPROPERTY(EditAnywhere, meta = (allowPrivateAccess = true, BindWidget))
	UWidget* gameOverText;

	//게임 클리어 텍스트
	UPROPERTY(EditAnywhere, meta = (allowPrivateAccess = true, BindWidget))
	UWidget* gameClearText;

	//점수 텍스트가 있는 세로 박스
	UPROPERTY(EditAnywhere, meta = (allowPrivateAccess = true, BindWidget))
	UWidget* scoreBox;

	//점수 텍스트
	UPROPERTY(EditAnywhere, meta = (allowPrivateAccess = true, BindWidget))
	class UTextBlock* scoreText;
};
