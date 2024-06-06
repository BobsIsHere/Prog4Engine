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

	private:
		friend class Singleton<BombManager>;

		BombManager();
		virtual ~BombManager();

		int m_MaxBombs;
		int m_CurrentBombs;
		std::vector<BombComponent*> m_pBombs; 
	};
}