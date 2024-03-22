#include "ScoreComponent.h"
#include "ScoreCommand.h"
#include "GameObject.h"

dae::ScoreCommand::ScoreCommand(GameObject* actor) :
	GameActorCommand{ actor }
{
}

dae::ScoreCommand::~ScoreCommand()
{
}

void dae::ScoreCommand::Execute(float)
{
	auto scoreComponent{ GetGameActor()->GetComponent<ScoreComponent>() };
	if (scoreComponent)
	{
		scoreComponent->IncreaseScore(100);
	}
}
