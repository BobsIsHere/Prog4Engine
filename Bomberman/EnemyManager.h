#pragma once
#include <vector>
#include "Singleton.h"

namespace dae
{
	class GameObject;

	class EnemyManager final : public Singleton<EnemyManager>
	{
	public:
		bool AllEnemiesDead();

		void AddEnemy(GameObject* pGameObject);
		void RemoveEnemy(GameObject* pGameObject);
		
	private:
		friend class Singleton<EnemyManager>;

		EnemyManager();
		virtual ~EnemyManager();

		std::vector<GameObject*> m_pEnemies;
		int m_TotalEnemies;
		int m_DestroyedEnemies;
	};
}