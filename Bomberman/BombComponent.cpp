#include "BombComponent.h"
#include "GameObject.h"
#include "Observer.h"
#include "Subject.h"

dae::BombComponent::BombComponent(GameObject* pGameObject) :
	UpdateComponent{ pGameObject },
	m_pSubject{ std::make_unique<Subject>() }, 
	m_IsTimerRunning{ false },
	m_StartTime{},
	m_GridSize{ 32 },
	m_BombDuration{ 3.f }  
{
}

dae::BombComponent::~BombComponent()
{
}

void dae::BombComponent::Update()
{
	BombTimer();
}

void dae::BombComponent::StartBombTimer() 
{
	m_StartTime = std::chrono::high_resolution_clock::now(); 
	m_IsTimerRunning = true; 
	 
	m_pSubject->NotifyObservers(GetGameObject(), Event::Event_Bomb_Dropped); 
}

void dae::BombComponent::ExplodeBomb()
{
	m_pSubject->NotifyObservers(GetGameObject(), Event::Event_Bomb_Exploded); 

	//Logic for handling explosion

	GetGameObject()->SetForRemoval();
}

void dae::BombComponent::BombTimer()
{
	if (m_IsTimerRunning)
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_StartTime).count();

		if (duration >= m_BombDuration)
		{
			ExplodeBomb();
			m_IsTimerRunning = false;
		}
	}
}
