#include "BombComponent.h"
#include "BombCommand.h"
#include "GameObject.h"

dae::BombCommand::BombCommand(GameObject* actor) :
	GameActorCommand{ actor }
{
}

dae::BombCommand::~BombCommand()
{
}

void dae::BombCommand::Execute()
{
	if (GetGameActor()->HasComponent<BombComponent>())
	{
		GetGameActor()->GetComponent<BombComponent>()->StartBombTimer();
	}
}
