#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

UCLASS()
class NBC_TASK8_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	//위젯 반환
	class UMainUserWidget* GetUserWidget();

private:
	//위젯
	UPROPERTY(EditAnywhere, Category = "User Widget", meta = (AllowPrivateAccess = "true"))
	UMainUserWidget* mainUserWidget;
};
