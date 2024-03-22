#include "ScoreComponent.h"
#include "Observer.h"
#include "Subject.h"

dae::ScoreComponent::ScoreComponent(GameObject* gameObject) :
	UpdateComponent{ gameObject },
	m_Score{},
	m_pSubject{ std::make_unique<Subject>() }
{
}

dae::ScoreComponent::~ScoreComponent()
{
}

void dae::ScoreComponent::Update(float)
{
}

void dae::ScoreComponent::IncreaseScore(int amount)
{
	m_Score += amount;
	m_pSubject->NotifyObservers(GetGameObject(), Event::Event_Score_Changed);
}

void dae::ScoreComponent::SetScore(int amount)
{
	m_Score = amount;
	m_pSubject->NotifyObservers(GetGameObject(), Event::Event_Score_Changed); 
}

void dae::ScoreComponent::AddObserver(Observer* observer)
{
	m_pSubject->AddObserver(observer);
}

int dae::ScoreComponent::GetScore() const
{
	return m_Score;
}
