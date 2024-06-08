#include "GameStateManager.h"

dae::GameStateManager::GameStateManager()
{
	m_pCurrentState = new MenuState();
	m_pCurrentState->OnEnter();
}

dae::GameStateManager::~GameStateManager()
{
	delete m_pCurrentState; 
	m_pCurrentState = nullptr; 
}

void dae::GameStateManager::Update()
{
	m_pCurrentState->Update();
	HandleInput();
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

		delete m_pCurrentState;
		m_pCurrentState = nullptr;

		m_pCurrentState = newState;  
		m_pCurrentState->OnEnter();  
	}
}
