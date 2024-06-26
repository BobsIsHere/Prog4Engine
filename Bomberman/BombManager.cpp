#include "AudioServiceLocator.h"
#include "GameAudioSystem.h"
#include "BombManager.h"

dae::BombManager::BombManager() :
	m_MaxBombs{ 1 },
	m_CurrentBombs{ 0 },
	m_ExplosionRange{ 1 },
	m_DetonatorEnabled{ false }
{
}

dae::BombManager::~BombManager() 
{
}

void dae::BombManager::AddBomb(BombComponent* bomb)
{
	if (CanSpawnBomb())
	{
		bomb->SetExplosionRange(m_ExplosionRange);  
		bomb->SetCanDetonate(m_DetonatorEnabled);

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

void dae::BombManager::IncreaseExplosionRange(int amount)
{
	m_ExplosionRange += amount; 
}

int dae::BombManager::GetExplosionRange() const
{
	return m_ExplosionRange;
}

void dae::BombManager::EnableDetonator(bool enable)
{
	m_DetonatorEnabled = enable;
}

void dae::BombManager::DetonateAllBombs()
{
	if (m_DetonatorEnabled)
	{
		for (auto bomb : m_pBombs)
		{
			bomb->DetonateBomb();
		}
	}
}
