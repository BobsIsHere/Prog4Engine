#pragma once
#include "UpdateComponent.h"

namespace dae
{
	class GameObject;

	class BombComponent final : public UpdateComponent
	{
	public:
		BombComponent(GameObject* pGameObject);
		virtual ~BombComponent();

		BombComponent(const BombComponent& other) = delete;
		BombComponent(BombComponent&& other) = delete;
		BombComponent& operator=(const BombComponent& other) = delete;
		BombComponent& operator=(BombComponent&& other) = delete;

		virtual void Update() override;

	private:
		void BombTimer();

		std::chrono::high_resolution_clock::time_point m_StartTime;
	};
}