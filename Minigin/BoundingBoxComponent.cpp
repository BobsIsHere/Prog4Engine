#include "BoundingBoxComponent.h"
#include "GameObject.h"

dae::BoundingBoxComponent::BoundingBoxComponent(GameObject* pGameObject, int width, int height) :
	UpdateComponent{ pGameObject }
{
	m_pGameObject = pGameObject;

	m_BoundingBox.x = static_cast<int>(m_pGameObject->GetWorldPosition().x); 
	m_BoundingBox.y = static_cast<int>(m_pGameObject->GetWorldPosition().y);
	m_BoundingBox.width = width; 
	m_BoundingBox.height = height; 
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
		m_BoundingBox.x = static_cast<int>(currentPos.x);
		m_BoundingBox.y = static_cast<int>(currentPos.y); 

		lastPos = currentPos;
	}
}

dae::Rect dae::BoundingBoxComponent::GetBoundingBox() const
{
	return m_BoundingBox;
}

void dae::BoundingBoxComponent::SetBoundingBox(int width, int height)
{
	m_BoundingBox.width = width;
	m_BoundingBox.height = height;
}
