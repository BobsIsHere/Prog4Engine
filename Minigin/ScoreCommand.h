#pragma once
#include "GameActorCommand.h"

namespace dae 
{
	class ScoreCommand final : public GameActorCommand 
	{
	public:
		ScoreCommand(GameObject* actor);
		virtual ~ScoreCommand();

		ScoreCommand(const ScoreCommand& other) = delete;
		ScoreCommand(ScoreCommand&& other) = delete;
		ScoreCommand& operator=(const ScoreCommand& other) = delete;
		ScoreCommand& operator=(ScoreCommand&& other) = delete;

		virtual void Execute(float deltaTime);
	};
}