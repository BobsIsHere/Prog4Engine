#include <memory>
#include "ChaserBehaviorComponent.h"
#include "MovementCommand.h"

dae::ChaserBehaviorComponent::ChaserBehaviorComponent(GameObject* pGameObject, const float speed, const GameObject* pPlayer) :
	UpdateComponent(pGameObject),
	m_Speed{ speed },
	m_MoveDirection{},
	m_DecisionTime{ 5.f },
	m_SightRange{ 80.f },
	m_ElapsedTime{},
	m_pPlayer{ pPlayer } 
{
	// Providing a seed value
	srand((unsigned)time(NULL));
}

dae::ChaserBehaviorComponent::~ChaserBehaviorComponent()
{
}

void dae::ChaserBehaviorComponent::Update()
{
	m_ElapsedTime += DeltaTime::GetInstance().GetDeltaTime();

	if (m_ElapsedTime >= m_DecisionTime)
	{
		if (CanSeePlayer())
		{
			glm::vec3 direction{ m_pPlayer->GetTransformComponent().GetLocalPosition() - GetGameObject()->GetLocalPosition() }; 
			m_MoveDirection = glm::normalize(direction);
		}
		else
		{
			// Randomly choose a direction
			const int direction = rand() % 3;

			switch (direction)
			{
				//Left
			case 0:
				m_MoveDirection = glm::vec3{ -1, 0, 0 };
				break;
				//Right
			case 1:
				m_MoveDirection = glm::vec3{ 1, 0, 0 };
				break;
				//Up
			case 2:
				m_MoveDirection = glm::vec3{ 0, 1, 0 };
				break;
				//Down
			case 3:
				m_MoveDirection = glm::vec3{ 0, -1, 0 };
				break;
			}
		}
	}

	const std::unique_ptr<MovementCommand> movementCommand{ std::make_unique<MovementCommand>(GetGameObject(), m_MoveDirection, m_Speed) };
	movementCommand->Execute();
}

void dae::ChaserBehaviorComponent::SetDirection(const glm::vec3& direction)
{
	m_MoveDirection = direction;
}

bool dae::ChaserBehaviorComponent::CanSeePlayer() const
{
	float distance{ glm::distance(GetGameObject()->GetLocalPosition(), m_pPlayer->GetTransformComponent().GetLocalPosition()) };

	return distance <= m_SightRange;
}
