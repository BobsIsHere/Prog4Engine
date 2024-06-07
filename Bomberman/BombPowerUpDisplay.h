#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class GameObject; 

	class BombPowerUpDisplay final : public Observer, public Component
	{
	public:
		BombPowerUpDisplay(GameObject* pGameObject);
		virtual ~BombPowerUpDisplay();

		virtual void Render() const {};
		virtual void Update() {}; 

		void Notify(GameObject* actor, Event event) override;
	};
}