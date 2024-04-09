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

void dae::BoundingBoxComponent::Update(float)
{
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
