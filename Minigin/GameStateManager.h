#pragma once
#include <memory>
#include "GameStateInterface.h"

namespace dae
{
	class GameStateManager
	{
	public:
		void Update();
		void Render();
		void HandleInput();

	private:
		GameStateInterface* m_pCurrentState;
	};
}