#pragma once
#include "GameActorCommand.h"

namespace dae
{
	class DetonateCommand final : public GameActorCommand
	{
	public:
		DetonateCommand(GameObject* actor);
		virtual ~DetonateCommand();

		DetonateCommand(const DetonateCommand& other) = delete;
		DetonateCommand(DetonateCommand&& other) = delete;
		DetonateCommand& operator=(const DetonateCommand& other) = delete;
		DetonateCommand& operator=(DetonateCommand&& other) = delete;

		virtual void Execute() override;
	};
}