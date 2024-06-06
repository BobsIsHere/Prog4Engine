#include "BoundingBoxComponent.h"
#include "CollisionSystem.h"
#include "GameObject.h"

dae::CollisionSystem::CollisionSystem() :
	m_pGameObjects{}
{
}

dae::CollisionSystem::~CollisionSystem()
{
}

void dae::CollisionSystem::AddGameObject(GameObject* pGameObject)
{
	m_pGameObjects.push_back(pGameObject);
}

void dae::CollisionSystem::RemoveGameObject(GameObject* pGameObject)
{
	m_pGameObjects.erase(std::remove(m_pGameObjects.begin(), m_pGameObjects.end(), pGameObject), m_pGameObjects.end());
}

std::vector<dae::GameObject*> dae::CollisionSystem::GetAllGameObjects() const
{
	return m_pGameObjects;
}

bool dae::CollisionSystem::IsColliding(GameObject* a, GameObject* b) const
{
	// Check for nullptr
	if (!a || !b)
	{
		return false;
	}

	// Check if either object is set for removal
	if (a->GetIsSetForRemoval() || b->GetIsSetForRemoval())
	{
		return false;
	}

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
