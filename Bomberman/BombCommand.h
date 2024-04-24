#pragma once
#include "GameActorCommand.h"

namespace dae
{
	class BombCommand final : public GameActorCommand
	{
	public:
		BombCommand(GameObject* actor);
		virtual ~BombCommand();

		BombCommand(const BombCommand& other) = delete;
		BombCommand(BombCommand&& other) = delete;
		BombCommand& operator=(const BombCommand& other) = delete;
		BombCommand& operator=(BombCommand&& other) = delete;

		virtual void Execute() override;
	};
}