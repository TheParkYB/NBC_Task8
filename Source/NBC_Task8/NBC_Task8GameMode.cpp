#include "NBC_Task8GameMode.h"
#include "NBC_Task8Character.h"
#include "UObject/ConstructorHelpers.h"

ANBC_Task8GameMode::ANBC_Task8GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
