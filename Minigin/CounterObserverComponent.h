#pragma once
#include "Observer.h"
#include "Component.h"
#include "GameObject.h"

namespace dae 
{
	class CounterObserverComponent final : public Observer, public Component
	{
	public:
		CounterObserverComponent(GameObject* gameObject);
		virtual ~CounterObserverComponent();

		virtual void Render() const {};
		virtual void RenderGui() {};
		virtual void Update(float) {};

		void Notify(GameObject* gameObject, Event event) override;
	};
}