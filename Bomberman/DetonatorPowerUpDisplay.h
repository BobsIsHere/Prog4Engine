#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class GameObject;

	class DetonatorPowerUpDisplay final : public Observer, public Component
	{
	public:
		DetonatorPowerUpDisplay(GameObject* pGameObject);
		virtual ~DetonatorPowerUpDisplay();

		virtual void Render() const {};
		virtual void Update() {};

		void Notify(GameObject* actor, Event event) override;
	};
}