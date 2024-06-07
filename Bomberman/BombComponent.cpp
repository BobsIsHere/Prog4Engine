#include "BoundingBoxComponent.h"
#include "ExplosionComponent.h"
#include "TextureComponent.h"
#include "BombComponent.h"
#include "BombManager.h"
#include "GameObject.h"

// Scene
#include "SceneManager.h"
#include "Scene.h"

// Audio
#include "AudioServiceLocator.h"
#include "GameAudioSystem.h"

dae::BombComponent::BombComponent(GameObject* pGameObject) :
	UpdateComponent{ pGameObject },
	m_IsTimerRunning{ false },
	m_StartTime{},
	m_GridSize{ 32 },
	m_BombDuration{ 3.f },
	m_ExplosionRange{ 0 },
	m_CanDetonate{}
{
}

dae::BombComponent::~BombComponent()
{
}

void dae::BombComponent::Update()
{ 
	if (!m_CanDetonate) 
	{
		BombTimer(); 
	}
}

void dae::BombComponent::StartBombTimer() 
{
	m_StartTime = std::chrono::high_resolution_clock::now(); 
	m_IsTimerRunning = true; 
	 
	dae::AudioServiceLocator::GetAudioSystem().PlaySoundEffect("../Data/Audio/BombermanDropsBomb.wav", 0.5f);
}

void dae::BombComponent::ExplodeBomb()
{
	const float gridSize{ 32.f };   

	// Function to create explosion object
	auto CreateExplosion = [this](const std::string& texture, float x, float y)
	{
		auto explosionObject = std::make_unique<GameObject>("Explosion");
		explosionObject->AddComponent<ExplosionComponent>(std::make_unique<ExplosionComponent>(explosionObject.get()));
		explosionObject->AddComponent<TextureComponent>(std::make_unique<TextureComponent>(explosionObject.get(), 2.f));
		explosionObject->AddComponent<BoundingBoxComponent>(std::make_unique<BoundingBoxComponent>(explosionObject.get(), 32.f, 32.f));
		explosionObject->GetComponent<TextureComponent>()->SetTexture(texture);
		explosionObject->SetLocalPosition(GetGameObject()->GetLocalPosition().x + x, GetGameObject()->GetLocalPosition().y + y); 

		SceneManager::GetInstance().GetActiveScene()->Add(std::move(explosionObject));
	};

	// Create middle explosion object
	CreateExplosion(m_ExplotionMiddleTexture, 0.f, 0.f);

	// Create explosion in all directions based on explosion range
	for (size_t idx = 1; idx <= m_ExplosionRange; ++idx) 
	{
		float offset{ gridSize * idx }; 

		// Top
		std::string topTexture{ idx == m_ExplosionRange ? m_ExplotionEndTopTexture : m_ExplotionVerticalTexture }; 
		CreateExplosion(topTexture, 0.f, -offset);

		// Bottom
		std::string bottomTexture{ idx == m_ExplosionRange ? m_ExplotionEndBottomTexture : m_ExplotionVerticalTexture };
		CreateExplosion(bottomTexture, 0.f, offset);

		// Right
		std::string rightTexture{ idx == m_ExplosionRange ? m_ExplotionEndRightTexture : m_ExplotionHorizontalTexture };
		CreateExplosion(rightTexture, offset, 0.f);

		// Left
		std::string leftTexture{ idx == m_ExplosionRange ? m_ExplotionEndLeftTexture : m_ExplotionHorizontalTexture };
		CreateExplosion(leftTexture, -offset, 0.f);
	}

	dae::AudioServiceLocator::GetAudioSystem().PlaySoundEffect("../Data/Audio/BombermanExplosion.wav", 0.75f);
	dae::BombManager::GetInstance().RemoveBomb(this);
	
	GetGameObject()->SetParent(nullptr, false);
	GetGameObject()->SetForRemoval();
}

void dae::BombComponent::SetExplosionRange(int range)
{
	m_ExplosionRange = range;
}

void dae::BombComponent::DetonateBomb()
{
	ExplodeBomb();
}

void dae::BombComponent::SetCanDetonate(bool canDetonate)
{
	m_CanDetonate = canDetonate;
}

void dae::BombComponent::BombTimer()
{
	if (m_IsTimerRunning and !m_CanDetonate)
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_StartTime).count();

		if (duration >= m_BombDuration)
		{
			ExplodeBomb();
			m_IsTimerRunning = false;
		}
	}
}
