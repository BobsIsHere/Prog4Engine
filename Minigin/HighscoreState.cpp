#include <iostream>
#include <algorithm>

#include "HighscoreState.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "MenuState.h"

void dae::HighscoreState::Update()
{
}

void dae::HighscoreState::Render()
{
}

void dae::HighscoreState::OnEnter()
{
	SceneManager::GetInstance().SetActiveScene("bombermanHighscore");

	m_FileStream.open("../Data/Highscores.txt", std::ios::in);

	if (!m_FileStream)
	{
		std::cerr << "Error opening highscore file!\n";
		return;
	}

	std::string line;
	while (std::getline(m_FileStream, line))
	{
		size_t commaPos = line.find(',');

		if (commaPos != std::string::npos)
		{
			std::string name = line.substr(0, commaPos);
			int score = std::stoi(line.substr(commaPos + 1));

			m_Highscores.emplace_back(std::make_pair(name, score));
		}
	}

	std::sort(m_Highscores.begin(), m_Highscores.end(), [](const auto& highscore1, const auto& highscore2)
		{
			return highscore1.second > highscore2.second; 
		}
	);
}

void dae::HighscoreState::OnExit()
{
	//clear any error flags
	m_FileStream.clear();

	//move write position of file to beginning
	m_FileStream.seekp(0);

	for (const auto& highscore : m_Highscores)
	{
		m_FileStream << highscore.first << "," << highscore.second << std::endl;
	}

	m_FileStream.close();
}

dae::GameStateInterface* dae::HighscoreState::HandleInput()
{
	if (InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_RETURN))
	{
		return new MenuState();
	}

	return nullptr;
}
