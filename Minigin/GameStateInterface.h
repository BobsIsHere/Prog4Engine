#pragma once

namespace dae
{
	class GameStateInterface
	{
	public:
		GameStateInterface() = default;
		virtual ~GameStateInterface() = default;

		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void OnEnter() = 0;
		virtual void OnExit() = 0; 
		virtual GameStateInterface* HandleInput() = 0;
	};
}