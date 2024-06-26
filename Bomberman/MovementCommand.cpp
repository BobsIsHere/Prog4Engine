#include "MovementCommand.h"
#include "GameObject.h"
#include "DeltaTime.h"

dae::MovementCommand::MovementCommand(GameObject* actor, glm::vec3 direction, float speed) :
	GameActorCommand{ actor },
	m_Direction{ direction },
	m_Speed{ speed }
{
}

dae::MovementCommand::~MovementCommand()
{
}

void dae::MovementCommand::Execute()
{
	const float deltaTime{ DeltaTime::GetInstance().GetDeltaTime() };
	
	auto position{ GetGameActor()->GetTransformComponent().GetLocalPosition() + (m_Direction * m_Speed * deltaTime) };
	GetGameActor()->SetLocalPosition(position);
}
