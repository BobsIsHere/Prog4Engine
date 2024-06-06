#pragma once
#include "Observer.h"
#include "Component.h"

namespace dae
{
	class GameObject; 

	class PowerUpDisplay final : public Observer, public Component
	{
	public:
		PowerUpDisplay(GameObject* pGameObject);
		virtual ~PowerUpDisplay();

		virtual void Render() const {};
		virtual void Update() {}; 

		void Notify(GameObject* actor, Event event) override;
	};
}