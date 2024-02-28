#include "TransformComponent.h"

dae::TransformComponent::TransformComponent(std::weak_ptr<GameObject> pGameObject) :
	Component{ pGameObject },
	m_LocalPosition{},
	m_WorldPosition{}
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

void dae::TransformComponent::SetLocalPosition(float x, float y, float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
}

void dae::TransformComponent::SetWorldPosition(float x, float y, float z)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
	m_WorldPosition.z = z;
}
