#pragma once
#include <memory>
#include <vector>
#include "Singleton.h"

namespace dae
{
	class GameObject;

	class CollisionSystem final : public Singleton<CollisionSystem>
	{
	public:
		void Update();

		void AddBoundingBox(GameObject* pGameObject);
		void RemoveBoundingBox(GameObject* pGameObject);

	private:
		CollisionSystem() = default;
		~CollisionSystem() = default;

		CollisionSystem(const CollisionSystem&) = delete;
		CollisionSystem& operator=(const CollisionSystem&) = delete;

		bool IsColliding(GameObject* a, GameObject* b) const;

		std::vector<GameObject*> m_pGameObjects;
	};
}