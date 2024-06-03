#include "BoundingBoxComponent.h"
#include "CollisionSystem.h"
#include "EnemyComponent.h"
#include "GameObject.h"

dae::EnemyComponent::EnemyComponent(GameObject* pGameObject) :
	UpdateComponent(pGameObject)
{
}

dae::EnemyComponent::~EnemyComponent()
{
}

void dae::EnemyComponent::Update()
{
	auto& collisionInstance = CollisionSystem::GetInstance();

	if (GetGameObject()->GetObjectTypeIdentifier() == "Enemy")
	{
		for (auto gameObject : collisionInstance.GetAllGameObjects())
		{
			if (gameObject->GetObjectTypeIdentifier() != "Enemy" and collisionInstance.IsColliding(GetGameObject(), gameObject))
			{
				if (gameObject->GetObjectTypeIdentifier() == "Breakable" or gameObject->GetObjectTypeIdentifier() == "Border")
				{
					const auto enemyBoundingBox{ GetGameObject()->GetComponent<BoundingBoxComponent>()->GetBoundingBox() };
					const auto blockBoundingBox{ gameObject->GetComponent<BoundingBoxComponent>()->GetBoundingBox() };

					const float overlapLeft{ enemyBoundingBox.x + enemyBoundingBox.width - blockBoundingBox.x };
					const float overlapRight{ blockBoundingBox.x + blockBoundingBox.width - enemyBoundingBox.x };
					const float overlapTop{ enemyBoundingBox.y + enemyBoundingBox.height - blockBoundingBox.y };
					const float overlapBottom{ blockBoundingBox.y + blockBoundingBox.height - enemyBoundingBox.y };

					const float minoverlapX{ std::min(overlapLeft, overlapRight) };
					const float minoverlapY{ std::min(overlapTop, overlapBottom) };

					if (minoverlapX < minoverlapY)
					{
						if (overlapLeft < overlapRight)
						{
							GetGameObject()->SetLocalPosition(blockBoundingBox.x - enemyBoundingBox.width, enemyBoundingBox.y);
						}
						else
						{
							GetGameObject()->SetLocalPosition(blockBoundingBox.x + blockBoundingBox.width, enemyBoundingBox.y);
						}
					}
					else
					{
						if (overlapTop < overlapBottom)
						{
							GetGameObject()->SetLocalPosition(enemyBoundingBox.x, blockBoundingBox.y - enemyBoundingBox.height);
						}
						else
						{
							GetGameObject()->SetLocalPosition(enemyBoundingBox.x, blockBoundingBox.y + blockBoundingBox.height);
						}
					}
				}
			}
		}
	}
}
