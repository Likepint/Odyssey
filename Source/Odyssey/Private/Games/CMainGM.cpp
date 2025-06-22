#include "Games/CMainGM.h"
#include "Global.h"

ACMainGM::ACMainGM()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, TEXT("/Script/Engine.Blueprint'/Game/Characters/Misthios/BP_CCharacter_Misthios.BP_CCharacter_Misthios_C'"));
}
