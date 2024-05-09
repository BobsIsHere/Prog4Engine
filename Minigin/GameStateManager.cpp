#include "GameStateManager.h"

void dae::GameStateManager::Update()
{
	m_pCurrentState->Update();
}

void dae::GameStateManager::Render()
{
	m_pCurrentState->Render();
}

void dae::GameStateManager::HandleInput()
{
	auto newState = m_pCurrentState->HandleInput(); 

	if (newState != nullptr)  
	{
		m_pCurrentState->OnExit();  
		m_pCurrentState = newState;  
		m_pCurrentState->OnEnter();  
	}
}
