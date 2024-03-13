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

	protected:
		GameObject* GetGameActor() const;

	private:
		GameObject* m_pGameActor; 
	};
}