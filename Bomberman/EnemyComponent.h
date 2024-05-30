#pragma once
#include "UpdateComponent.h"

namespace dae
{
	class EnemyComponent final : public UpdateComponent 
	{
	public:
		EnemyComponent(GameObject* pGameObject);
		virtual ~EnemyComponent();

		EnemyComponent(const EnemyComponent& other) = delete;
		EnemyComponent(EnemyComponent&& other) = delete;
		EnemyComponent& operator=(const EnemyComponent& other) = delete;
		EnemyComponent& operator=(EnemyComponent&& other) = delete;

		virtual void Update() override;
	};
}