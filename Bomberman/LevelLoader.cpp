#include <iostream>
#include <fstream>
#include <memory>

#include "BoundingBoxComponent.h"
#include "TextureComponent.h"
#include "LevelLoader.h"
#include "GameObject.h"

dae::LevelLoader::LevelLoader() :
	m_TileSize{ 32.f }, 
	m_UISize{ 64.f },
	m_FilePath{}
{
}

dae::LevelLoader::~LevelLoader()
{
}

void dae::LevelLoader::Initialize(const std::string& filePath, Scene& scene)
{
	m_FilePath = filePath; 
	m_pScene = &scene;
}

void dae::LevelLoader::LoadLevel()
{
	if (!m_pScene)
	{
		std::cout << "LevelLoader is not initialized correctly with a Scene!" << std::endl;
		return;
	}

	std::ifstream file{ m_FilePath }; 
	if (!file.is_open())
	{
		std::cerr << "Could not open file: " << m_FilePath << std::endl;
		return;
	}

	std::string line{};
	while (std::getline(file, line))
	{
		size_t spacePos = line.find(' ');
		if (spacePos != std::string::npos)
		{
			const float x{ std::stof(line.substr(0, spacePos)) };
			const float y{ std::stof(line.substr(spacePos + 1)) };

			CreateBlock(x, y);
		}
	}

	file.close();
}

void dae::LevelLoader::CreateBlock(float x, float y)
{
	auto brickObject = std::make_unique<dae::GameObject>("Breakable");
	brickObject->SetLocalPosition(x * m_TileSize, (y * m_TileSize) + m_UISize);
	brickObject->AddComponent<dae::TextureComponent>(std::make_unique<dae::TextureComponent>(brickObject.get(), 2.f));
	brickObject->AddComponent<dae::BoundingBoxComponent>(std::make_unique<dae::BoundingBoxComponent>(brickObject.get(), 32.f, 32.f));

	brickObject->GetComponent<dae::TextureComponent>()->SetTexture("Brick.png");
	m_pScene->Add(std::move(brickObject));
}
