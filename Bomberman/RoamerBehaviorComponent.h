#pragma once
#include "GameObject.h"
#include "EnemyBehaviorComponent.h"

namespace dae
{
	class RoamerBehaviorComponent final : public EnemyBehaviorComponent
	{
	public:
		RoamerBehaviorComponent(GameObject* pGameObject, const float speed);
		virtual ~RoamerBehaviorComponent();
	};
}