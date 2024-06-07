#pragma once
#include <chrono>
#include <memory>
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

		void StartBombTimer();
		void ExplodeBomb();
		void SetExplosionRange(int range); 
		void DetonateBomb();
		void SetCanDetonate(bool canDetonate);

	private:
		void BombTimer();

		std::chrono::high_resolution_clock::time_point m_StartTime;

		bool m_IsTimerRunning;
		bool m_CanDetonate;

		const int m_GridSize;
		int m_ExplosionRange;
		float m_BombDuration;

		const std::string m_ExplotionMiddleTexture{ "ExplosionMiddle.png" };
		const std::string m_ExplotionHorizontalTexture{ "ExplosionHorizontal.png" };
		const std::string m_ExplotionVerticalTexture{ "ExplosionVertical.png" };
		const std::string m_ExplotionEndLeftTexture{ "ExplosionEndLeft.png" };
		const std::string m_ExplotionEndRightTexture{ "ExplosionEndRight.png" };
		const std::string m_ExplotionEndTopTexture{ "ExplosionEndTop.png" };
		const std::string m_ExplotionEndBottomTexture{ "ExplosionEndBottom.png" };
	};
}