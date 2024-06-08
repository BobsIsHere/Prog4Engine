#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	m_pActiveScene->Update();
}

void dae::SceneManager::Render()
{
	m_pActiveScene->Render(); 
}

void dae::SceneManager::SetActiveScene(const std::string& name)
{
	for (const auto& scene : m_pScenes)
	{
		if (scene->GetSceneName() == name)
		{
			m_pPrevScene = m_pActiveScene;
			m_pActiveScene = scene;
			return;
		}
	}

	throw std::runtime_error("No scene with name " + name + " found");
}

dae::Scene& dae::SceneManager::GetNextScene(const std::string sceneName)
{
	bool returnNext = false;
	// Loop through all scenes
	for (const auto& s : m_pScenes)
	{
		// If we are the scene to be returned
		if (returnNext)
		{
			return *s;
		}
		// If the current scene is the active scene
		if (s->GetSceneName() == sceneName)
		{
			// Then we must return the next scene
			returnNext = true;
		}
	}
	return *m_pScenes.front();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene{ name });

	if (m_pScenes.empty())
	{
		m_pActiveScene = scene; 
	}

	m_pScenes.push_back(scene);
	return *scene;
}
