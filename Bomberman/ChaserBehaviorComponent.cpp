#include <memory>
#include "ChaserBehaviorComponent.h"
#include "MovementCommand.h"

dae::ChaserBehaviorComponent::ChaserBehaviorComponent(GameObject* pGameObject, const float speed, const GameObject* pPlayer) :
	EnemyBehaviorComponent(pGameObject, speed), 
	m_SightRange{ 80.f },
	m_pPlayer{ pPlayer } 
{
	// Providing a seed value
	srand((unsigned)time(NULL));
}

dae::ChaserBehaviorComponent::~ChaserBehaviorComponent()
{
}

void dae::ChaserBehaviorComponent::Move()
{
	if (m_pPlayer)
	{
		const glm::vec3 playerPos{ m_pPlayer->GetTransformComponent().GetLocalPosition() };
		const glm::vec3 enemyPos{ GetGameObject()->GetLocalPosition() };
		const float distance{ glm::distance(playerPos, enemyPos) };

		if (distance <= m_SightRange)
		{
			const glm::vec3 direction{ glm::normalize(playerPos - enemyPos) };
			SetDirection(direction);
		}
	}

	EnemyBehaviorComponent::Move();
}
