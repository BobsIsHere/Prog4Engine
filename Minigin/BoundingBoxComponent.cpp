#include "BoundingBoxComponent.h"
#include "CollisionSystem.h"
#include "GameObject.h"

dae::BoundingBoxComponent::BoundingBoxComponent(GameObject* pGameObject, float width, float height) :
	UpdateComponent{ pGameObject }
{
	m_pGameObject = pGameObject;

	m_BoundingBox.x = m_pGameObject->GetWorldPosition().x; 
	m_BoundingBox.y = m_pGameObject->GetWorldPosition().y;
	m_BoundingBox.width = width; 
	m_BoundingBox.height = height; 

	CollisionSystem::GetInstance().AddGameObject(GetGameObject()); 
}

dae::BoundingBoxComponent::~BoundingBoxComponent()
{
}

void dae::BoundingBoxComponent::Update()
{
	const glm::vec2 currentPos{ m_pGameObject->GetWorldPosition() };
	glm::vec2 lastPos{ m_BoundingBox.x, m_BoundingBox.y };

	if (currentPos != lastPos)
	{
		m_BoundingBox.x = currentPos.x;
		m_BoundingBox.y = currentPos.y; 

		lastPos = currentPos;
	}
}

dae::BoundingBoxComponent::Rect dae::BoundingBoxComponent::GetBoundingBox() const
{
	return m_BoundingBox;
}

void dae::BoundingBoxComponent::SetBoundingBox(float width, float height)
{
	m_BoundingBox.width = width;
	m_BoundingBox.height = height;
}
