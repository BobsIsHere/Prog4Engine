#pragma once
#include "GameStateInterface.h"

namespace dae
{
	class LevelCompleteState final : public GameStateInterface
	{
	public:
		LevelCompleteState() = default;
		virtual ~LevelCompleteState() = default;

		virtual void Update() override;
		virtual void Render() override;
		virtual void OnEnter() override;
		virtual void OnExit() override;
		virtual GameStateInterface* HandleInput() override;

	private:
		const float m_TimeToWait = 3.f;
		float m_AccumulatedTime = 0.f;
	};
}