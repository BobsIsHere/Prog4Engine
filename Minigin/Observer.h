#pragma once
namespace dae 
{
	class GameObject; 

	enum struct Event
	{
		Event_Player_Hit,
		Event_Player_Died,
		Event_Score_Changed,
		Event_Bomb_Dropped,
		Event_Bomb_Exploded
	};
	
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(GameObject* gameObject, Event event) = 0;
	};
}

