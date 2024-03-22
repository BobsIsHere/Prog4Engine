#include "CounterComponent.h"
#include "GameObject.h"

dae::CounterComponent::CounterComponent(GameObject* gameObject) :
	UpdateComponent{ gameObject },
	m_Value{},
	m_MaxValue{},
	m_pSubject{ std::make_unique<Subject>() }
{
}

dae::CounterComponent::~CounterComponent()
{
}

void dae::CounterComponent::Update(float)
{
}

void dae::CounterComponent::Increment(int amount)
{
	m_Value += amount;
	m_pSubject->NotifyObservers(GetGameObject(), Event::Event_Player_Hit);
}

void dae::CounterComponent::Decrement(int amount)
{
	m_Value -= amount;
	m_pSubject->NotifyObservers(GetGameObject(), Event::Event_Player_Hit);
}

void dae::CounterComponent::SetValue(int amount)
{
	m_Value = amount;
}

void dae::CounterComponent::AddObserver(Observer* observer)
{
	m_pSubject->AddObserver(observer);
}

int dae::CounterComponent::GetValue() const
{
	return m_Value;
}
