#include <chrono>
#include "BombComponent.h"
#include "GameObject.h"

dae::BombComponent::BombComponent(GameObject* pGameObject) :
	UpdateComponent{ pGameObject }
{
	m_StartTime = std::chrono::high_resolution_clock::now();
}

dae::BombComponent::~BombComponent()
{
}

void dae::BombComponent::Update()
{
	BombTimer();
}

void dae::BombComponent::BombTimer()
{
	const auto totalTime{ std::chrono::duration_cast<std::chrono::duration<float>>(m_StartTime.time_since_epoch()) };

	if (totalTime.count() >= 3.f)
	{
		//Explode
	}
}
