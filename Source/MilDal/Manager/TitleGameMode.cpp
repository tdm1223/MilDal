#include "MilDal/Manager/TitleGameMode.h"
#include "MilDal/Player/UIPlayerController.h"

ATitleGameMode::ATitleGameMode()
{
    ConstructorHelpers::FClassFinder<AUIPlayerController> controller(*FString(TEXT("Class'/Script/MilDal.UIPlayerController'")));

    DefaultPawnClass = APawn::StaticClass();
    PlayerControllerClass = controller.Class;
}