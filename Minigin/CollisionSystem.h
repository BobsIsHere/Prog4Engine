#pragma once
#include <vector>
#include "Collidable.h"

namespace dae
{
	class CollisionSystem
	{
	public:


	private:
		CollisionSystem() = default;
		~CollisionSystem() = default;

		std::vector<Collidable> m_Collidables;
	};
}