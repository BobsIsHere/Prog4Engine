#include <string>
#include <chrono>
#include "FPSComponent.h"
#include "GameObject.h"

dae::FPSComponent::FPSComponent(std::weak_ptr<GameObject> pGameObject) :
	UpdateComponent{ pGameObject },
	m_FrameCount{},
	m_TotalTime{}
{
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
		std::ostringstream fpsString{};
		fpsString << std::fixed << std::setprecision(1) << (m_FrameCount / m_TotalTime) << " FPS";
		m_pGameObject.lock()->GetComponent<dae::TextComponent>()->SetText(fpsString.str());

		m_FrameCount = 0;
		m_TotalTime = 0.f;
	}
}
