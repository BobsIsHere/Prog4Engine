#include "DetonatorPowerUpDisplay.h"
#include "FlamesPowerUpDisplay.h"
#include "BoundingBoxComponent.h"
#include "BombPowerUpDisplay.h"
#include "PlayerComponent.h"
#include "CollisionSystem.h"
#include "GameObject.h"
#include "Observer.h"
#include "Subject.h"

dae::PlayerComponent::PlayerComponent(GameObject* pGameObject) :
	UpdateComponent(pGameObject),
	m_pSubject{ std::make_unique<Subject>() }
{
}

dae::PlayerComponent::~PlayerComponent()
{
}

void dae::PlayerComponent::Update()
{
	auto& collisionInstance = CollisionSystem::GetInstance();

	if (GetGameObject()->GetObjectTypeIdentifier() == "Player")
	{
		for (auto gameObject : collisionInstance.GetAllGameObjects())
		{
			if (gameObject->GetObjectTypeIdentifier() != "Player" and collisionInstance.IsColliding(GetGameObject(), gameObject)) 
			{
				if (gameObject->GetObjectTypeIdentifier() == "Enemy") 
				{
					//Bomberman loses a life
					//Bomberman respawns
					//Reload level
				}
				else if (gameObject->GetObjectTypeIdentifier() == "BombPowerUp")
				{
					//Bomberman gains a power-up
					m_pSubject->NotifyObservers(GetGameObject(), Event::Event_Extra_Bomb_PowerUp_PickedUp);  

					//Power-up disappears
					CollisionSystem::GetInstance().RemoveGameObject(gameObject);
					m_pSubject->RemoveObserver(gameObject->GetComponent<dae::BombPowerUpDisplay>());
					gameObject->SetForRemoval();
				}
				else if (gameObject->GetObjectTypeIdentifier() == "FlamePowerUp")
				{
					//Bomberman gains a power-up
					m_pSubject->NotifyObservers(GetGameObject(), Event::Event_Flame_PowerUp_PickedUp); 

					//Power-up disappears
					CollisionSystem::GetInstance().RemoveGameObject(gameObject);
					m_pSubject->RemoveObserver(gameObject->GetComponent<dae::FlamesPowerUpDisplay>());
					gameObject->SetForRemoval(); 
				}
				else if (gameObject->GetObjectTypeIdentifier() == "DetonatorPowerUp") 
				{
					//Bomberman gains a power-up
					m_pSubject->NotifyObservers(GetGameObject(), Event::Event_Detonator_PowerUp_PickedUp);  

					//Power-up disappears
					CollisionSystem::GetInstance().RemoveGameObject(gameObject);
					m_pSubject->RemoveObserver(gameObject->GetComponent<dae::DetonatorPowerUpDisplay>());
					gameObject->SetForRemoval();  
				}
				else if (gameObject->GetObjectTypeIdentifier() == "Border" or gameObject->GetObjectTypeIdentifier() == "Breakable")
				{
					const auto playerBoundingBox{ GetGameObject()->GetComponent<BoundingBoxComponent>()->GetBoundingBox() };
					const auto blockBoundingBox{ gameObject->GetComponent<BoundingBoxComponent>()->GetBoundingBox() }; 

					const float overlapLeft{ playerBoundingBox.x + playerBoundingBox.width - blockBoundingBox.x };
					const float overlapRight{ blockBoundingBox.x + blockBoundingBox.width - playerBoundingBox.x }; 
					const float overlapTop{ playerBoundingBox.y + playerBoundingBox.height - blockBoundingBox.y };
					const float overlapBottom{ blockBoundingBox.y + blockBoundingBox.height - playerBoundingBox.y };

					const float minoverlapX{ std::min(overlapLeft, overlapRight) };
					const float minoverlapY{ std::min(overlapTop, overlapBottom) };

					if (minoverlapX < minoverlapY)
					{
						if (overlapLeft < overlapRight)
						{
							GetGameObject()->SetLocalPosition(blockBoundingBox.x - playerBoundingBox.width, playerBoundingBox.y); 
						}
						else
						{
							GetGameObject()->SetLocalPosition(blockBoundingBox.x + blockBoundingBox.width, playerBoundingBox.y); 
						}
					}
					else
					{
						if (overlapTop < overlapBottom)
						{
							GetGameObject()->SetLocalPosition(playerBoundingBox.x, blockBoundingBox.y - playerBoundingBox.height);  
						}
						else
						{
							GetGameObject()->SetLocalPosition(playerBoundingBox.x, blockBoundingBox.y + blockBoundingBox.height);  
						}
					}
				}
			}
		}
	}
}

void dae::PlayerComponent::AddObserver(Observer* observer)
{
	m_pSubject->AddObserver(observer);
}
