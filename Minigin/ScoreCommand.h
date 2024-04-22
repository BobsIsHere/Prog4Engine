#pragma once
#include "GameActorCommand.h"

namespace dae 
{
	class GameObject;

	class ScoreCommand final : public GameActorCommand 
	{
	public:
		ScoreCommand(GameObject* actor, const int score);
		virtual ~ScoreCommand();

		ScoreCommand(const ScoreCommand& other) = delete;
		ScoreCommand(ScoreCommand&& other) = delete;
		ScoreCommand& operator=(const ScoreCommand& other) = delete;
		ScoreCommand& operator=(ScoreCommand&& other) = delete;

		virtual void Execute();

	private:
		int m_Score;
	};
}