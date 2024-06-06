#pragma once
#include "Observer.h"
#include "Component.h"

namespace dae 
{
	class GameObject;

	class HealthDisplay final : public Observer, public Component
	{
	public:
		HealthDisplay(GameObject* gameObject);
		virtual ~HealthDisplay();

		virtual void Render() const {};
		virtual void Update() {};
		
		void Notify(GameObject* gameObject, Event event) override;
		void UpdateText(GameObject* gameObject);
	};
}