#include "AchievementDisplay.h"
#include "ScoreComponent.h"
#include "GameObject.h"

dae::AchievementDisplay::AchievementDisplay(GameObject* pGameObject) :
	Component{ pGameObject },
	m_GotAchievement{ false }
{
}

dae::AchievementDisplay::~AchievementDisplay()
{
}

void dae::AchievementDisplay::Notify(GameObject* pGameObject, Event event) 
{
	const int achievementScore{ 500 };
	
	switch (event)
	{
	case dae::Event::Event_Score_Changed:
		if (!m_GotAchievement)
		{
			if (pGameObject->HasComponent<ScoreComponent>())
			{
				if (pGameObject->GetComponent<ScoreComponent>()->GetScore() >= achievementScore)
				{
					SteamUserStats()->SetAchievement("ACH_WIN_ONE_GAME");
					SteamUserStats()->StoreStats();

					m_GotAchievement = true;
				}
			}
		}
		break;
	}
}
