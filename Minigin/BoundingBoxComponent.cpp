#include "BoundingBoxComponent.h"
#include "GameObject.h"

dae::BoundingBoxComponent::BoundingBoxComponent(GameObject* pGameObject) :
	UpdateComponent{ pGameObject },
	m_Width{},
	m_Height{}
{
	m_pGameObject = pGameObject;

	m_BoundingBox.x = static_cast<int>(m_pGameObject->GetWorldPosition().x); 
	m_BoundingBox.y = static_cast<int>(m_pGameObject->GetWorldPosition().y);
	m_BoundingBox.width = m_Width; 
	m_BoundingBox.height = m_Height; 
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

dae::BoundingBoxComponent::Rect dae::BoundingBoxComponent::GetBoundingBox() const
{
	return m_BoundingBox;
}

void dae::BoundingBoxComponent::SetBoundingBox(int width, int height)
{
	m_Width = width;
	m_Height = height;
}
