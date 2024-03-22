#pragma once
#include <vector>
#include "Observer.h"

namespace dae 
{
	class GameObject;

	class Subject final
	{
	public:
		Subject() = default;
		~Subject() = default;

		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void NotifyObservers(GameObject* gameObject, Event event) const;

	private:
		std::vector<Observer*> m_Observers;
	};
}