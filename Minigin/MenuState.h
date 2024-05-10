#pragma once
#include <memory>
#include "GameStateInterface.h"

namespace dae
{
	class MenuState final : public GameStateInterface
	{
	public:
		MenuState() = default;
		~MenuState() = default;

		virtual void Update() override;
		virtual void Render() override;
		virtual void OnEnter() override;
		virtual void OnExit() override;
		virtual GameStateInterface* HandleInput() override;
	};
}