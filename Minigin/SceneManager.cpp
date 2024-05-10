#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	m_ActiveScene->Update();
}

void dae::SceneManager::Render()
{
	m_ActiveScene->Render(); 
}

void dae::SceneManager::SetActiveScene(const std::string& name)
{
	for (const auto& scene : m_Scenes)
	{
		if (scene->GetSceneName() == name)
		{
			m_ActiveScene = scene;
			return;
		}
	}

	throw std::runtime_error("No scene with name " + name + " found");
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene{ name });
	m_Scenes.push_back(scene);
	return *scene;
}
