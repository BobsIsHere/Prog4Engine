#include <string>
#include "TimerComponent.h"
#include "GameObject.h"
#include "DeltaTime.h"

dae::TimerComponent::TimerComponent(GameObject* pGameObject) :
	UpdateComponent(pGameObject),
	m_pTextComponent{ nullptr },
	m_TimeLimit{ 0 },
	m_TimeRemaining{ 0 }
{
	if (!pGameObject->HasComponent<TextComponent>())
	{
		pGameObject->AddComponent<TextComponent>(std::make_unique<TextComponent>(pGameObject));
	}

	m_pTextComponent = pGameObject->GetComponent<TextComponent>();
}

dae::TimerComponent::~TimerComponent()
{
}

void dae::TimerComponent::Update()
{
	if (m_TimeRemaining > 0.f)
	{
		m_TimeRemaining -= DeltaTime::GetInstance().GetDeltaTime();

		if (m_TimeRemaining <= 0.f) 
		{
			// do something
		}

		if (m_pTextComponent)
		{
			std::string timeString = std::to_string(static_cast<int>(m_TimeRemaining));
			m_pTextComponent->SetText("TIME " + timeString);
		}
	}
}

float dae::TimerComponent::GetTimeRemaining() const
{
	return m_TimeRemaining;
}

void dae::TimerComponent::SetTimeLimit(float timeLimit)
{
	m_TimeLimit = timeLimit;
	m_TimeRemaining = timeLimit; 
}
