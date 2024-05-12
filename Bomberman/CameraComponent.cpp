#include "CameraComponent.h"
#include "GameObject.h"

dae::CameraComponent::CameraComponent(GameObject* pGameObject) : 
	UpdateComponent(pGameObject),
	m_CameraWidth{ 640.f },
	m_CameraHeight{ 480.f },
	m_LevelBoundries{ {0.f, 0.f}, 2040.f, 484.f },
	m_pGameObject{ pGameObject }
{
}

dae::CameraComponent::~CameraComponent() 
{
}

void dae::CameraComponent::Update()
{
	Point2i position{ m_pGameObject->GetTransformComponent().GetLocalPosition().x,
					  m_pGameObject->GetTransformComponent().GetLocalPosition().y };

	float width{ m_pGameObject->GetTransformComponent().GetWidth() };
	float height{ m_pGameObject->GetTransformComponent().GetHeight() };

	Recti cameraRect{ GetCameraRect(Recti{position, width, height}) };
	m_pGameObject->GetTransformComponent().SetWorldPosition(cameraRect.position.x, cameraRect.position.y);
}

void dae::CameraComponent::SetLevelBoundres(const Recti& levelBoundries)
{ 
	m_LevelBoundries = levelBoundries; 
}

void dae::CameraComponent::Clamp(Point2i& bottomLeftPos) const
{
	float levelMinX{ m_LevelBoundries.position.x };
	float levelMaxX{ m_LevelBoundries.position.x + m_LevelBoundries.width };

	if (bottomLeftPos.x < levelMinX)
	{
		bottomLeftPos.x = levelMinX;
	}
	else if (bottomLeftPos.x + m_CameraWidth > levelMaxX)
	{
		bottomLeftPos.x = levelMaxX - m_CameraWidth;
	}
}

void dae::CameraComponent::Transform(const Recti& rect) const
{
	Point2i bottomLeftPos{ Track(rect) };
}

dae::CameraComponent::Point2i dae::CameraComponent::Track(const Recti& target) const
{
	Point2i targetCenter{ target.position.x + target.width / 2, target.position.y + target.height / 2 }; 
	return Point2i{ targetCenter.x - m_CameraWidth / 2, targetCenter.y - m_CameraHeight / 2 };
}

dae::CameraComponent::Recti dae::CameraComponent::GetCameraRect(const Recti actorShape) const
{
	Point2i temp{ Track(actorShape) };
	Clamp(temp);

	return Recti{ temp.x, temp.y, m_CameraWidth, m_CameraHeight };
}
