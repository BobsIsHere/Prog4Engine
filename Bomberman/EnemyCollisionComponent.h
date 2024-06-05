#pragma once
#include "UpdateComponent.h"
#include "GameObject.h"

namespace dae
{
	class EnemyCollisionComponent final : public UpdateComponent 
	{
	public:
		EnemyCollisionComponent(GameObject* pGameObject);
		virtual ~EnemyCollisionComponent();

		EnemyCollisionComponent(const EnemyCollisionComponent& other) = delete;
		EnemyCollisionComponent(EnemyCollisionComponent&& other) = delete;
		EnemyCollisionComponent& operator=(const EnemyCollisionComponent& other) = delete;
		EnemyCollisionComponent& operator=(EnemyCollisionComponent&& other) = delete;

		virtual void Update() override;
		void ChangeDirection(const glm::vec3& direction);
	};
}
