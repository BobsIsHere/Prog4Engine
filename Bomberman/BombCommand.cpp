#include "BombCommand.h"

dae::BombCommand::BombCommand(GameObject* actor) :
	GameActorCommand{ actor }
{
}

dae::BombCommand::~BombCommand()
{
}

void dae::BombCommand::Execute()
{
}
