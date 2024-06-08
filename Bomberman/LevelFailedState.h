#pragma once
#include "GameStateInterface.h"

namespace dae
{
	class LevelFailedState final : public GameStateInterface
	{
	public:
		LevelFailedState() = default;
		virtual ~LevelFailedState() = default;

		virtual void Update() override;
		virtual void Render() override;
		virtual void OnEnter() override;
		virtual void OnExit() override;
		virtual GameStateInterface* HandleInput() override;
	};
}