#pragma once
#include <steam_api.h>

#include "Observer.h"
#include "Component.h"

namespace dae
{
	class GameObject;

	class AchievementDisplay final : public Observer, public Component
	{
	public:
		AchievementDisplay(GameObject* pGameObject);
		virtual ~AchievementDisplay();

		virtual void Render() const {};
		virtual void RenderGui() {};
		virtual void Update(float) {};

		virtual void Notify(GameObject* pGameObject, Event event) override;
	};
}