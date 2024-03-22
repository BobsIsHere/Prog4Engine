#include "Subject.h"

void dae::Subject::AddObserver(Observer* observer)
{
	m_Observers.push_back(observer);
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	std::erase(m_Observers, observer);
}

void dae::Subject::NotifyObservers(GameObject* gameObject, Event event) const
{
	for (auto observer : m_Observers)
	{
		observer->Notify(gameObject, event); 
	}
}
