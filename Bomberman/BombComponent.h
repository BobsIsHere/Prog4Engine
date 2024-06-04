#pragma once
#include <chrono>
#include <memory>
#include "UpdateComponent.h"

namespace dae
{
	class GameObject;
	class Observer;
	class Subject;

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

		void AddObserver(Observer* observer);

		void StartBombTimer();
		void ExplodeBomb();

	private:
		void BombTimer();

		std::unique_ptr<Subject> m_pSubject;

		std::chrono::high_resolution_clock::time_point m_StartTime;

		bool m_IsTimerRunning;

		const int m_GridSize;
		float m_BombDuration;
	};
}