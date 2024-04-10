#include <SDL_stdinc.h>
#include "RotationComponent.h"
#include "GameObject.h"
#include "DeltaTime.h"

dae::RotationComponent::RotationComponent(GameObject* pGameObject) :
	UpdateComponent{ pGameObject },
	m_RotationAngle{},
	m_RotationSpeed{ 180.f },
	m_Distance{}
{
	m_Distance = sqrt(powf((pGameObject->GetTransformComponent().GetLocalPosition().x ), 2) 
						+ powf((pGameObject->GetTransformComponent().GetLocalPosition().y), 2));
}

dae::RotationComponent::~RotationComponent()
{
}

void dae::RotationComponent::Update()
{
	const float deltaTime{ DeltaTime::GetInstance().GetDeltaTime() };
	
	m_RotationAngle += (m_RotationSpeed * deltaTime) * float(M_PI)/ 180.f;

	GetGameObject()->GetTransformComponent().SetLocalPosition(cosf(m_RotationAngle) * m_Distance, 
																	 sinf(m_RotationAngle) * m_Distance);
}

void dae::RotationComponent::SetRotationSpeed(const float& speed)
{
	m_RotationSpeed = speed;
}
