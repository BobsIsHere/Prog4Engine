#include "DeltaTime.h"

void dae::DeltaTime::UpdateDeltaTime()
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto deltaTime = std::chrono::duration<float>(currentTime - m_LastTime).count();
	m_LastTime = currentTime;
	m_DeltaTime = deltaTime;
}

float dae::DeltaTime::GetDeltaTime() const
{
	return m_DeltaTime;
}
