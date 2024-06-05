#pragma once
#include "GameObject.h"
#include "UpdateComponent.h"

namespace dae
{
	class RoamerBehaviorComponent final : public UpdateComponent
	{
	public:
		RoamerBehaviorComponent(GameObject* pGameObject, const float speed, glm::vec3 moveDirection);
		virtual ~RoamerBehaviorComponent();

		RoamerBehaviorComponent(const RoamerBehaviorComponent& other) = delete;
		RoamerBehaviorComponent(RoamerBehaviorComponent&& other) = delete;
		RoamerBehaviorComponent& operator=(const RoamerBehaviorComponent& other) = delete;
		RoamerBehaviorComponent& operator=(RoamerBehaviorComponent&& other) = delete;

		virtual void Update() override;
		void SetDirection(const glm::vec3& direction); 

	private:
		bool IsAlignedWithGrid() const;

		const float m_Speed;
		const float m_DecisionTime;
		float m_ElapsedTime;

		glm::vec3 m_MoveDirection;
	};
}