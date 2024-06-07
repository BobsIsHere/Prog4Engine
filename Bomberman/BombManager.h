#pragma once
#include <memory>
#include <vector>

#include "Singleton.h"
#include "BombComponent.h"

namespace dae
{
	class BombManager final : public Singleton<BombManager>
	{
	public:
		void AddBomb(BombComponent* bomb); 
		void RemoveBomb(BombComponent* bomb);

		bool CanSpawnBomb() const;
		void IncreaseBombLimit(int amount);

		void IncreaseExplosionRange(int amount);
		int GetExplosionRange() const;

		void EnableDetonator(bool enable);
		void DetonateAllBombs();

	private:
		friend class Singleton<BombManager>;

		BombManager();
		virtual ~BombManager();

		bool m_DetonatorEnabled;
		int m_MaxBombs;
		int m_CurrentBombs;
		int m_ExplosionRange;
		std::vector<BombComponent*> m_pBombs; 
	};
}