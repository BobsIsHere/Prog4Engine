#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class GameObject;

	class FlamesPowerUpDisplay final : public Observer, public Component
	{
	public:
		FlamesPowerUpDisplay(GameObject* pGameObject);
		virtual ~FlamesPowerUpDisplay();

		virtual void Render() const {};
		virtual void Update() {};

		void Notify(GameObject* actor, Event event) override;
	};
}