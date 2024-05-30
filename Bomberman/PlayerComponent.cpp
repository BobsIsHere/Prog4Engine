#include "BoundingBoxComponent.h"
#include "PlayerComponent.h"
#include "CollisionSystem.h"
#include "GameObject.h"

dae::PlayerComponent::PlayerComponent(GameObject* pGameObject) :
	UpdateComponent(pGameObject)
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
				else if (gameObject->GetObjectTypeIdentifier() == "PowerUp")
				{
					//Bomberman gains a power-up
					//Power-up disappears
				}
				else
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
