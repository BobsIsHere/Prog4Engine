#include "BoundingBoxComponent.h"
#include "CollisionSystem.h"
#include "GameObject.h"

void dae::CollisionSystem::Update()
{
}

void dae::CollisionSystem::AddBoundingBox(GameObject* pGameObject)
{
	m_pGameObjects.push_back(pGameObject);
}

void dae::CollisionSystem::RemoveBoundingBox(GameObject* pGameObject)
{
	m_pGameObjects.erase(std::remove(m_pGameObjects.begin(), m_pGameObjects.end(), pGameObject), m_pGameObjects.end());
}

bool dae::CollisionSystem::IsColliding(GameObject* a, GameObject* b) const
{
	if (a->HasComponent<BoundingBoxComponent>() and b->HasComponent<BoundingBoxComponent>())
	{
		const auto aBoundingBox = a->GetComponent<BoundingBoxComponent>()->GetBoundingBox();
		const auto bBoundingBox = b->GetComponent<BoundingBoxComponent>()->GetBoundingBox();

		if (aBoundingBox.x < bBoundingBox.x + bBoundingBox.width and
			aBoundingBox.x + aBoundingBox.width > bBoundingBox.x and
			aBoundingBox.y < bBoundingBox.y + bBoundingBox.height and
			aBoundingBox.y + aBoundingBox.height > bBoundingBox.y)
		{
			return true;
		}

		return false;
	}

	return false;
}

void dae::CollisionSystem::HandleCollision(GameObject* a, GameObject* b)
{
	int objectA = a->GetObjectType();
	int objectB = b->GetObjectType();

	if (objectA == 1)
	{
		if (objectB == 2) 
		{
			// Prevent player from moving through breakable blocks
			// Implement collision response here
		}
		else if (objectB == 3) 
		{
			// Prevent player from moving through unbreakable blocks
			// Implement collision response here
		}
	}
}
