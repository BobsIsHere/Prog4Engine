#include "TransformComponent.h"
#include "GameObject.h"

dae::TransformComponent::TransformComponent(GameObject* pGameObject) :
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

void dae::TransformComponent::RenderGui()
{
}

void dae::TransformComponent::SetLocalPosition(float x, float y, float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
	
	const auto pParent = GetGameObject()->GetParent();
	if (pParent != nullptr)
	{
		const auto parentsWorldPos{ pParent->GetTransformComponent().GetWorldPosition() };
		SetWorldPosition(parentsWorldPos.x + x, parentsWorldPos.y + y);
	}
	else
	{
		SetWorldPosition(x, y ,z);
	}
}

void dae::TransformComponent::SetWorldPosition(float x, float y, float z)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
	m_WorldPosition.z = z;
}
