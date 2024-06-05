#include <iostream>
#include "ExplosionComponent.h"
#include "CollisionSystem.h"
#include "GameObject.h"
#include "DeltaTime.h"

dae::ExplosionComponent::ExplosionComponent(GameObject* pGameObject) :
	UpdateComponent( pGameObject ),
	m_ExplosionDuration{ 1.f },
	m_AnimationTimer{ 0.f }
{
}

dae::ExplosionComponent::~ExplosionComponent()
{
}

void dae::ExplosionComponent::Update()
{
	m_AnimationTimer += DeltaTime::GetInstance().GetDeltaTime();

	if (m_AnimationTimer >= m_ExplosionDuration)
	{
		GetGameObject()->SetForRemoval();
		std::cout << "Set for removal" << std::endl; 
	}
}

void dae::ExplosionComponent::CheckCollision()
{
	auto& collisionInstance = CollisionSystem::GetInstance();

	if (GetGameObject()->GetObjectTypeIdentifier() == "Explosion")
	{
		for (auto gameObject : collisionInstance.GetAllGameObjects())
		{
			if (collisionInstance.IsColliding(GetGameObject(), gameObject))
			{
				if (gameObject->GetObjectTypeIdentifier() == "Player") 
				{
					//Bomberman loses a life
					//Bomberman respawns
					//Reload level
				}
				else if (gameObject->GetObjectTypeIdentifier() == "Enemy")
				{
					//Enemy dies
					//Bomberman gains points
				}
				else if (gameObject->GetObjectTypeIdentifier() == "Breakable")
				{
					//Block disappears
				}
			}
		}
	}
}
