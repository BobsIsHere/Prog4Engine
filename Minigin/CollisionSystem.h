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
		void AddGameObject(GameObject* pGameObject);
		void RemoveGameObject(GameObject* pGameObject);

		std::vector<GameObject*> GetAllGameObjects() const;

		bool IsColliding(GameObject* a, GameObject* b) const; 

	private:
		friend class Singleton<CollisionSystem>;

		CollisionSystem();
		virtual ~CollisionSystem();

		std::vector<GameObject*> m_pGameObjects;
	};
}