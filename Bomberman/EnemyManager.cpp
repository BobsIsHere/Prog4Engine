#include "EnemyManager.h"
#include "GameObject.h"

dae::EnemyManager::EnemyManager() :
	m_pEnemies{},
	m_TotalEnemies{},
	m_DestroyedEnemies{}
{
}

dae::EnemyManager::~EnemyManager() 
{
}

bool dae::EnemyManager::AllEnemiesDead()
{
	if (m_DestroyedEnemies == m_TotalEnemies)
	{
		m_DestroyedEnemies = 0;
		return true;
	}

	return false;
}

void dae::EnemyManager::AddEnemy(GameObject* pGameObject)
{
	m_pEnemies.push_back(pGameObject);
	++m_TotalEnemies;
}

void dae::EnemyManager::RemoveEnemy(GameObject* pGameObject)
{
	auto it = std::find(m_pEnemies.begin(), m_pEnemies.end(), pGameObject);

	if (it != m_pEnemies.end()) 
	{
		m_pEnemies.erase(it);

		++m_DestroyedEnemies;
	}
}
