#include "HealthCommand.h"
#include "GameObject.h"
#include "HealthComponent.h"

dae::HealthCommand::HealthCommand(GameObject* actor) :
	GameActorCommand{ actor }
{
}

dae::HealthCommand::~HealthCommand()
{
}

void dae::HealthCommand::Execute()
{
	if (GetGameActor()->HasComponent<HealthComponent>()) 
	{
		GetGameActor()->GetComponent<HealthComponent>()->LowerLives(1);
	}
}
