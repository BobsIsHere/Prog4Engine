#include "AudioServiceLocator.h"
#include "GameAudioSystem.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "PlayingState.h"
#include "StageState.h"
#include "GameObject.h"
#include "DeltaTime.h"
#include "Renderer.h"
#include "Scene.h"

dae::StageState::StageState(const int stageNumber) :
	m_StageNumber{ stageNumber },
	m_SwitchingStateTimer{ 3.f },
	m_pStageText{}
{
}

dae::StageState::~StageState()
{
}

void dae::StageState::Update()
{
	m_SwitchingStateTimer -= DeltaTime::GetInstance().GetDeltaTime(); 
}

void dae::StageState::Render()
{
}

void dae::StageState::OnEnter()
{
	dae::AudioServiceLocator::GetAudioSystem().PlayMusic("../Data/Audio/StageStart.mp3", 1.f);

	auto& bombermanStageScene = SceneManager::GetInstance().CreateScene("bombermanStage");
	auto bombermanFont = dae::ResourceManager::GetInstance().LoadFont("bombermanFont.otf", 14);

	dae::SceneManager::GetInstance().SetActiveScene("bombermanStage");

	// Set backrgound to black
	Renderer::GetInstance().SetBackgroundColor(SDL_Color{ 0, 0, 0, 255 });  

	auto stageObject = std::make_unique<GameObject>();
	stageObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(stageObject.get()));
	stageObject->AddComponent<dae::TextComponent>(std::make_unique<dae::TextComponent>(stageObject.get()));
	stageObject->GetComponent<dae::TextComponent>()->SetText("Stage " + std::to_string(m_StageNumber));
	stageObject->GetComponent<dae::TextComponent>()->SetFont(bombermanFont);
	stageObject->SetLocalPosition(200, 230);

	bombermanStageScene.Add(std::move(stageObject));
}

void dae::StageState::OnExit() 
{ 
	dae::AudioServiceLocator::GetAudioSystem().StopMusic(); 
}

dae::GameStateInterface* dae::StageState::HandleInput() 
{
	if (m_SwitchingStateTimer <= 0.f)
	{
		return new PlayingState(); 
	}

	return nullptr;
}
