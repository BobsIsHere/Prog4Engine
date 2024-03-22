#include "CounterObserverComponent.h"

dae::CounterObserverComponent::CounterObserverComponent(GameObject* gameObject) :
	Component{ gameObject }
{
}

dae::CounterObserverComponent::~CounterObserverComponent()
{
}

void dae::CounterObserverComponent::Notify(GameObject* gameObject, Event event)
{
	switch (event)
	{
	case dae::Event::Event_Player_Hit:
		gameObject->GetParent();
		break;
	case dae::Event::Event_Enemy_Hit:
		break;
	case dae::Event::Event_Player_Died:
		break;
	case dae::Event::Event_Enemy_Died:
		break;
	case dae::Event::Event_Score_Changed:
		break;
	}
}
