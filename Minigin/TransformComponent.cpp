#include "TransformComponent.h"

dae::TransformComponent::TransformComponent(std::weak_ptr<GameObject> pGameObject) :
	Component{ pGameObject },
	m_Position{}
{
}

dae::TransformComponent::~TransformComponent()
{
}

void dae::TransformComponent::Update(float)
{
}

void dae::TransformComponent::Render() const
{
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}
