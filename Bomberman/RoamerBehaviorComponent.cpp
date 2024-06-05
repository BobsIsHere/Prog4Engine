#include <memory>

#include "RoamerBehaviorComponent.h"
#include "MovementCommand.h"
#include "DeltaTime.h"

dae::RoamerBehaviorComponent::RoamerBehaviorComponent(GameObject* pGameObject, const float speed, glm::vec3 moveDirection) :
	UpdateComponent(pGameObject),
	m_Speed{ speed },
	m_DecisionTime{ 3.f },
	m_ElapsedTime{},
	m_MoveDirection{ moveDirection }
{
}

dae::RoamerBehaviorComponent::~RoamerBehaviorComponent()
{
}

void dae::RoamerBehaviorComponent::Update()
{
	m_ElapsedTime += DeltaTime::GetInstance().GetDeltaTime();

	if (m_ElapsedTime >= m_DecisionTime)
	{
		// Providing a seed value
		srand((unsigned)time(NULL));

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

		m_ElapsedTime = 0.f;
	}
	
	const std::unique_ptr<MovementCommand> movementCommand{ std::make_unique<MovementCommand>(GetGameObject(), m_MoveDirection, m_Speed) };
	movementCommand->Execute();
}

void dae::RoamerBehaviorComponent::SetDirection(const glm::vec3& direction)
{
	m_MoveDirection = direction; 
}

bool dae::RoamerBehaviorComponent::IsAlignedWithGrid() const
{
	const float gridSize = 32.0f;
	const auto& position = GetGameObject()->GetLocalPosition();

	// Check if the position is aligned with the grid
	return (static_cast<int>(position.x) % static_cast<int>(gridSize) == 0) and
		   (static_cast<int>(position.y - 64) % static_cast<int>(gridSize) == 0);
}
