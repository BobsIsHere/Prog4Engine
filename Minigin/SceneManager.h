#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene; 

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update();
		void Render();

		void SetActiveScene(const std::string& name);
		std::shared_ptr<Scene> GetActiveScene() const { return m_pActiveScene; }
		std::shared_ptr<Scene> GetPreviousScene() const { return m_pPrevScene; }
		Scene& GetNextScene(const std::string sceneName);

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		std::shared_ptr<Scene> m_pActiveScene; 
		std::shared_ptr<Scene> m_pPrevScene;
		std::vector<std::shared_ptr<Scene>> m_pScenes; 
	};
}
