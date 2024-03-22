#include "HealthComponent.h"
#include "GameObject.h"
#include "Observer.h"
#include "Subject.h"

#include <iostream>

dae::HealthComponent::HealthComponent(GameObject* gameObject) : 
	UpdateComponent{ gameObject },
	m_Lives{ 3 },
	m_pSubject{ std::make_unique<Subject>() }
{
}

dae::HealthComponent::~HealthComponent()
{
}

void dae::HealthComponent::Update(float)
{
}

void dae::HealthComponent::LowerLives(int amount)
{
	m_Lives -= amount;
	std::cout << m_Lives << " lives left\n";

	if (m_Lives <= 0)
	{
		m_Lives = 0;
		m_pSubject->NotifyObservers(GetGameObject(), Event::Event_Player_Died);
	}

	m_pSubject->NotifyObservers(GetGameObject(), Event::Event_Player_Hit); 
}

void dae::HealthComponent::SetLives(int amount)
{
	m_Lives = amount; 
}

void dae::HealthComponent::AddObserver(Observer* observer)
{
	m_pSubject->AddObserver(observer); 
}

int dae::HealthComponent::GetLives() const
{
	return m_Lives;
}
