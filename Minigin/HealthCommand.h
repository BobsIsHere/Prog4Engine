#pragma once
#include "GameActorCommand.h"

namespace dae 
{
	class HealthCommand final : public GameActorCommand
	{
	public:
		HealthCommand(GameObject* actor);
		virtual ~HealthCommand();

		HealthCommand(const HealthCommand& other) = delete;
		HealthCommand(HealthCommand&& other) = delete;
		HealthCommand& operator=(const HealthCommand& other) = delete;
		HealthCommand& operator=(HealthCommand&& other) = delete;

		virtual void Execute(float deltaTime) override;
	};
}