#include "AudioServiceLocator.h"
#include "GameAudioSystem.h"
#include "BombManager.h"

dae::BombManager::BombManager() :
	m_MaxBombs{ 1 },
	m_CurrentBombs{ 0 }
{
}

dae::BombManager::~BombManager()
{
}

void dae::BombManager::AddBomb(BombComponent* bomb)
{
	if (CanSpawnBomb())
	{
		m_pBombs.push_back(bomb);
		++m_CurrentBombs;
	}
}

void dae::BombManager::RemoveBomb(BombComponent* bomb)
{
	auto it = std::find(m_pBombs.begin(), m_pBombs.end(), bomb);

	if (it != m_pBombs.end()) 
	{
		m_pBombs.erase(it); 
		--m_CurrentBombs; 
	}
}

bool dae::BombManager::CanSpawnBomb() const
{
	return m_CurrentBombs < m_MaxBombs;
}

void dae::BombManager::IncreaseBombLimit(int amount)
{
	m_MaxBombs += amount;
}
