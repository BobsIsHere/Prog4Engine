#pragma once
#include "Observer.h"
#include "Component.h"

namespace dae 
{
	class Gameobject;

	class HealthDisplay final : public Observer, public Component
	{
	public:
		HealthDisplay(GameObject* gameObject);
		virtual ~HealthDisplay();

		virtual void Render() const {};
		virtual void RenderGui() {};
		virtual void Update(float) {};
		
		void Notify(GameObject* gameObject, Event event) override;
		void UpdateText(GameObject* gameObject);
	};
}