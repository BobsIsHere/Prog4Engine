#pragma once
#include <memory>
#include "Singleton.h"
#include "MenuState.h"
#include "GameStateInterface.h"

namespace dae
{
	class GameStateManager final : public Singleton<GameStateManager>
	{
	public:
		virtual void Update();
		void Render();
		void HandleInput();

		GameStateInterface* GetCurrentState() const { return m_pCurrentState; }

	private:
		friend class Singleton<GameStateManager>;

		GameStateInterface* m_pCurrentState;

		GameStateManager();
		virtual ~GameStateManager();
	};
}