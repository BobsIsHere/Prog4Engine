#pragma once
#include "Observer.h"
#include "Component.h"

namespace dae
{
	class Gameobject;

	class ScoreDisplay final : public Observer, public Component
	{
	public:
		ScoreDisplay(GameObject* gameObject);
		virtual ~ScoreDisplay();

		virtual void Render() const {};
		virtual void RenderGui() {};
		virtual void Update(float) {};

		void Notify(GameObject* gameObject, Event event) override;
		void UpdateText(GameObject* gameObject);
	};
}