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
}

void dae::HighscoreState::OnExit()
{
	
}

dae::GameStateInterface* dae::HighscoreState::HandleInput()
{
	if (InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_RETURN))
	{
		return new MenuState();
	}

	return nullptr;
}
