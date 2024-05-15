#include "CameraComponent.h"
#include "GameObject.h"

dae::CameraComponent::CameraComponent(GameObject* pGameObject, float mapWidth, float screenWidth, float playableArea) :
	UpdateComponent(pGameObject),
	m_pGameObject{ pGameObject },
	m_MapWidth{ mapWidth },
	m_ScreenWidth{ screenWidth }, 
	m_PlayableAreaWidth{ playableArea } 
{
}

dae::CameraComponent::~CameraComponent() 
{
}

void dae::CameraComponent::Update()
{
	
}
