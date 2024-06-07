#include "DetonateCommand.h"
#include "BombManager.h"
#include "GameObject.h"

dae::DetonateCommand::DetonateCommand(GameObject* actor) :
	GameActorCommand(actor) 
{
}

dae::DetonateCommand::~DetonateCommand()
{
}

void dae::DetonateCommand::Execute()
{
	auto& pBombManager = BombManager::GetInstance();
	pBombManager.DetonateAllBombs();
}
