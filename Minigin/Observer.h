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
		Event_Bomb_Exploded,
		Event_Extra_Bomb_PowerUp_PickedUp,
		Event_Flame_PowerUp_PickedUp,
		Event_Detonator_PowerUp_PickedUp
	};
	
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(GameObject* gameObject, Event event) = 0;
	};
}

