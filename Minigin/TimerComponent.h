#pragma once
#include <memory>
#include "UpdateComponent.h"
#include "TextComponent.h"

namespace dae
{
	class GameObject;

	class TimerComponent final : public UpdateComponent
	{
	public:
		TimerComponent(GameObject* pGameObject);
		virtual ~TimerComponent();

		TimerComponent(const TimerComponent& other) = delete;
		TimerComponent(TimerComponent&& other) = delete;
		TimerComponent& operator=(const TimerComponent& other) = delete;
		TimerComponent& operator=(TimerComponent&& other) = delete;

		virtual void Update() override;

		float GetTimeRemaining() const;
		void SetTimeLimit(float timeLimit);

	private:
		float m_TimeLimit;
		float m_TimeRemaining;

		TextComponent* m_pTextComponent;  
	};
}