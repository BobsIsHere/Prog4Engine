#pragma once
#include <string>
#include <vector>
#include <fstream>

#include "GameStateInterface.h"

namespace dae
{
	class HighscoreState final : public GameStateInterface
	{
	public:
		HighscoreState() = default;
		virtual ~HighscoreState() = default;

		virtual void Update() override;
		virtual void Render() override;
		virtual void OnEnter() override;
		virtual void OnExit() override;
		virtual GameStateInterface* HandleInput() override;

	private:
		std::string m_PlayerName;
		std::vector<std::pair<std::string, int>> m_Highscores;
		std::fstream m_FileStream;
	};
}