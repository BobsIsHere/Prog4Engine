#include "EnemyCollisionComponent.h"
#include "RoamerBehaviorComponent.h"
#include "ChaserBehaviorComponent.h"
#include "BoundingBoxComponent.h"
#include "CollisionSystem.h"

dae::EnemyCollisionComponent::EnemyCollisionComponent(GameObject* pGameObject) :
	UpdateComponent(pGameObject)
{
}

dae::EnemyCollisionComponent::~EnemyCollisionComponent()
{
}

void dae::EnemyCollisionComponent::Update()
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

					// Calculate overlap between two bounding boxes in x-axis
					const float overlapLeft{ enemyBoundingBox.x + enemyBoundingBox.width - blockBoundingBox.x };
					const float overlapRight{ blockBoundingBox.x + blockBoundingBox.width - enemyBoundingBox.x };
					// Calculate overlap between two bounding boxes in y-axis
					const float overlapTop{ enemyBoundingBox.y + enemyBoundingBox.height - blockBoundingBox.y };
					const float overlapBottom{ blockBoundingBox.y + blockBoundingBox.height - enemyBoundingBox.y };

					// Find min. overlap in x-axis and y-axis
					const float minoverlapX{ std::min(overlapLeft, overlapRight) };
					const float minoverlapY{ std::min(overlapTop, overlapBottom) };

					// Move enemy to the side with the least overlap
					if (minoverlapX < minoverlapY)
					{
						if (overlapLeft < overlapRight)
						{
							// Move enemy to the left of the block
							GetGameObject()->SetLocalPosition(blockBoundingBox.x - enemyBoundingBox.width, enemyBoundingBox.y);

							ChangeDirection(glm::vec3{ -1, 0, 0 });
						}
						else
						{
							// Move enemy to the right of the block
							GetGameObject()->SetLocalPosition(blockBoundingBox.x + blockBoundingBox.width, enemyBoundingBox.y);

							ChangeDirection(glm::vec3{ 1, 0, 0 });
						}
					}
					else
					{
						if (overlapTop < overlapBottom)
						{
							// Move enemy to the top of the block
							GetGameObject()->SetLocalPosition(enemyBoundingBox.x, blockBoundingBox.y - enemyBoundingBox.height);

							ChangeDirection(glm::vec3{ 0, -1, 0 });
						}
						else
						{
							// Move enemy to the bottom of the block
							GetGameObject()->SetLocalPosition(enemyBoundingBox.x, blockBoundingBox.y + blockBoundingBox.height);

							ChangeDirection(glm::vec3{ 0, 1, 0 });
						}
					}
				}
			}
		}
	}
}

void dae::EnemyCollisionComponent::ChangeDirection(const glm::vec3& direction)
{
	if (GetGameObject()->HasComponent<RoamerBehaviorComponent>())
	{
		GetGameObject()->GetComponent<RoamerBehaviorComponent>()->SetDirection(direction);
	}
	else if (GetGameObject()->HasComponent<ChaserBehaviorComponent>())
	{
		GetGameObject()->GetComponent<ChaserBehaviorComponent>()->SetDirection(direction);
	}
}