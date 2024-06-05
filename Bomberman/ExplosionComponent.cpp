#include "ExplosionComponent.h"
#include "GameObject.h"
#include "DeltaTime.h"
#include <iostream>

dae::ExplosionComponent::ExplosionComponent(GameObject* pGameObject) :
	UpdateComponent( pGameObject ),
	m_ExplosionDuration{ 0.5f },
	m_AnimationTimer{ 0.f }
{
}

dae::ExplosionComponent::~ExplosionComponent()
{
}

void dae::ExplosionComponent::Update()
{
	if (GetGameObject()->GetParent() == nullptr)
	{
		return;
	}
	
	m_AnimationTimer += DeltaTime::GetInstance().GetDeltaTime();

	if (m_AnimationTimer >= m_ExplosionDuration)
	{
		GetGameObject()->SetParent(nullptr, false);
		GetGameObject()->SetForRemoval();
		std::cout << "Is set for removal explosion" << std::endl;
	}
}

void dae::ExplosionComponent::CheckCollision()
{
}
