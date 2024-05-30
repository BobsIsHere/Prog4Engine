#pragma once
#include "UpdateComponent.h"

namespace dae
{
	class GameObject;

	class PlayerComponent final : public UpdateComponent
	{
	public:
		PlayerComponent(GameObject* pGameObject);
		virtual ~PlayerComponent();

		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		virtual void Update() override;
	};
}