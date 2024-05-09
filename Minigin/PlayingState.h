#pragma once
#include "GameStateInterface.h"

namespace dae
{
	class PlayingState final : public GameStateInterface
	{
	public:
		PlayingState() = default;
		virtual ~PlayingState() = default;

		virtual void Update() override;
		virtual void Render() override;
		virtual void OnEnter() override;
		virtual void OnExit() override;
		virtual GameStateInterface* HandleInput() override;

	private:

	};
}