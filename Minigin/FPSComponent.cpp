#include <string>
#include <chrono>
#include <format>
#include <iomanip>
#include "FPSComponent.h"
#include "GameObject.h"

dae::FPSComponent::FPSComponent(GameObject* pGameObject) :
	UpdateComponent{ pGameObject },
	m_FrameCount{},
	m_TotalTime{}
{
	if (!pGameObject->HasComponent<TextComponent>())
	{
		pGameObject->AddComponent<TextComponent>(std::make_shared<TextComponent>(pGameObject));
	}

	m_pTextComponent = pGameObject->GetComponent<TextComponent>();
}

dae::FPSComponent::~FPSComponent()
{
}

void dae::FPSComponent::Update(float deltaTime)
{
	++m_FrameCount;
	m_TotalTime += deltaTime;

	if (m_TotalTime > 0.1f)
	{
		std::string fpsString = std::format("{:.1f} FPS", static_cast<float>(m_FrameCount) / m_TotalTime);
		m_pTextComponent->SetText(fpsString);

		m_FrameCount = 0;
		m_TotalTime = 0.f;
	}
}
