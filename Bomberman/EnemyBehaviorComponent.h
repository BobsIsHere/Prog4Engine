#pragma once
#include "UpdateComponent.h"
#include "GameObject.h"

namespace dae
{
	class EnemyBehaviorComponent : public UpdateComponent 
	{
	public:
		EnemyBehaviorComponent(GameObject* pGameObject, const float speed);
		virtual ~EnemyBehaviorComponent();

		EnemyBehaviorComponent(const EnemyBehaviorComponent& other) = delete;
		EnemyBehaviorComponent(EnemyBehaviorComponent&& other) = delete;
		EnemyBehaviorComponent& operator=(const EnemyBehaviorComponent& other) = delete;
		EnemyBehaviorComponent& operator=(EnemyBehaviorComponent&& other) = delete;

		virtual void Update() override;
		void SetDirection(const glm::vec3& direction);

	protected:
		virtual void Move();
		void RandomizeDirection();

		const float m_Speed;
		float m_AccumulatedTime;
		float m_SwitchTime;
		glm::vec3 m_MoveDirection;
	};
}