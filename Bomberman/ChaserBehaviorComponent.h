#pragma once
#include "UpdateComponent.h"
#include "GameObject.h"

namespace dae
{
	class ChaserBehaviorComponent final : public UpdateComponent
	{
	public:
		ChaserBehaviorComponent(GameObject* pGameObject, const float speed, const GameObject* pPlayer); 
		virtual ~ChaserBehaviorComponent();

		ChaserBehaviorComponent(const ChaserBehaviorComponent& other) = delete;
		ChaserBehaviorComponent(ChaserBehaviorComponent&& other) = delete;
		ChaserBehaviorComponent& operator=(const ChaserBehaviorComponent& other) = delete;
		ChaserBehaviorComponent& operator=(ChaserBehaviorComponent&& other) = delete;

		virtual void Update() override;
		void SetDirection(const glm::vec3& direction);

	private:
		bool CanSeePlayer() const;

		const float m_Speed;
		const float m_DecisionTime;
		const float m_SightRange;
		float m_ElapsedTime;

		glm::vec3 m_MoveDirection;

		const GameObject* m_pPlayer;
	};
}