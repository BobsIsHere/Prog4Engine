#pragma once
#include "EnemyBehaviorComponent.h"
#include "GameObject.h"

namespace dae
{
	class ChaserBehaviorComponent final : public EnemyBehaviorComponent 
	{ 
	public:
		ChaserBehaviorComponent(GameObject* pGameObject, const float speed, const GameObject* pPlayer); 
		virtual ~ChaserBehaviorComponent();

		ChaserBehaviorComponent(const ChaserBehaviorComponent& other) = delete;
		ChaserBehaviorComponent(ChaserBehaviorComponent&& other) = delete;
		ChaserBehaviorComponent& operator=(const ChaserBehaviorComponent& other) = delete;
		ChaserBehaviorComponent& operator=(ChaserBehaviorComponent&& other) = delete;

		virtual void Move() override;

	private:
		const float m_SightRange;
		const GameObject* m_pPlayer;
	};
}