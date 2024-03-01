#pragma once
#include "UpdateComponent.h"

namespace dae
{
	class RotationComponent final : public UpdateComponent
	{
	public:
		RotationComponent(GameObject* pGameObject);
		virtual ~RotationComponent();

		RotationComponent(const RotationComponent& other) = delete;
		RotationComponent(RotationComponent&& other) = delete;
		RotationComponent& operator=(const RotationComponent& other) = delete;
		RotationComponent& operator=(RotationComponent&& other) = delete;

		virtual void Update(float deltaTime) override;

		void SetRotationSpeed(const float& speed);

	private:
		float m_RotationAngle;
		float m_RotationSpeed;
		float m_Distance;
	};
}