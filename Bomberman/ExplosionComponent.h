#pragma once
#include "UpdateComponent.h"

namespace dae
{
	class ExplosionComponent final : public UpdateComponent
	{
	public:
		ExplosionComponent(GameObject* pGameObject);
		~ExplosionComponent();

		ExplosionComponent(const ExplosionComponent& other) = delete;
		ExplosionComponent(ExplosionComponent&& other) = delete;
		ExplosionComponent& operator=(const ExplosionComponent& other) = delete;
		ExplosionComponent& operator=(ExplosionComponent&& other) = delete;

		virtual void Update() override;

		void CheckCollision();

	private:
		const float m_ExplosionDuration;
		float m_AnimationTimer;
	};
}