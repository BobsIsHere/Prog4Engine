#pragma once
#include "IUpdateableObject.h"
#include "GameStateManager.h"

namespace dae
{
	class GameStateUpdater final : public IUpdateableObject
	{
	public:
		GameStateUpdater() {};
		virtual ~GameStateUpdater() = default;

		virtual void Update() override
		{
			dae::GameStateManager::GetInstance().Update();
		}
	};
}