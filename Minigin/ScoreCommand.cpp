#include "ScoreComponent.h"
#include "ScoreCommand.h"
#include "GameObject.h"

dae::ScoreCommand::ScoreCommand(GameObject* actor, const int score) :
	GameActorCommand{ actor },
	m_Score{ score }
{
}

dae::ScoreCommand::~ScoreCommand()
{
}

void dae::ScoreCommand::Execute()
{
	auto scoreComponent{ GetGameActor()->GetComponent<ScoreComponent>() };
	if (scoreComponent)
	{
		scoreComponent->IncreaseScore(m_Score);
	}
}
