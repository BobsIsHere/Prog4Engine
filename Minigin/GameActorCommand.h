#pragma once
#include "Command.h"

namespace dae
{
	class GameObject;

	class GameActorCommand : public Command
	{
	public:
		GameActorCommand(GameObject* actor);
		virtual ~GameActorCommand();

		GameActorCommand(const GameActorCommand& other) = delete;
		GameActorCommand(GameActorCommand&& other) = delete;
		GameActorCommand& operator=(const GameActorCommand& other) = delete;
		GameActorCommand& operator=(GameActorCommand&& other) = delete;

	protected:
		GameObject* GetGameActor() const;

	private:
		GameObject* m_pGameActor; 
	};
}