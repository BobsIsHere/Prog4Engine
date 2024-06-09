#pragma once
#include <string>
#include "Scene.h"
#include "Singleton.h"

namespace dae
{
	class LevelLoader final : public Singleton<LevelLoader>
	{
	public:
		void Initialize(const std::string& filePath, Scene& scene); 
		void LoadLevel();

	private:
		friend class Singleton<LevelLoader>;

		LevelLoader();
		virtual ~LevelLoader();

		void CreateBlock(float x, float y);

		const float m_TileSize;
		const float m_UISize;
		std::string m_FilePath;
		Scene* m_pScene;  
	};
}