#include "GameActorCommand.h"
#include "GameObject.h" 

dae::GameActorCommand::GameActorCommand(GameObject* actor) :
	m_pGameActor{ actor }
{
}

dae::GameActorCommand::~GameActorCommand()
{
}

dae::GameObject* dae::GameActorCommand::GetGameActor() const
{
	return m_pGameActor;
}
