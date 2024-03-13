#include "GameActorCommand.h"
#include "GameObject.h" 

dae::GameActorCommand::GameActorCommand(GameObject* actor) :
	m_pGameActor{ actor }
{
}

dae::GameActorCommand::~GameActorCommand()
{
	delete m_pGameActor;
	m_pGameActor = nullptr;
}

dae::GameObject* dae::GameActorCommand::GetGameActor() const
{
	return m_pGameActor;
}
