#pragma once
#include "GameStateInterface.h"

namespace dae
{
	class StageState final : public GameStateInterface
	{
	public:
		StageState();
		virtual ~StageState();

		virtual void Update() override;
		virtual void Render() override;
		virtual void OnEnter() override;
		virtual void OnExit() override;
		virtual GameStateInterface* HandleInput() override;

	private:
		int m_StageNumber;
		float m_SwitchingStateTimer;
	};
}