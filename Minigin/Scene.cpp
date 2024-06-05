#include "Scene.h"
#include "GameObject.h"
#include "AudioSystem.h"
#include "AudioServiceLocator.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_pObjects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_pObjects.erase(std::remove(m_pObjects.begin(), m_pObjects.end(), object), m_pObjects.end());
}

void Scene::RemoveAll()
{
	m_pObjects.clear();
}

void Scene::Update()
{
	for (auto& object : m_pObjects)
	{
		object->Update();
	}

	for (int objectIdx = 0; objectIdx < m_pObjects.size(); ++objectIdx)
	{
		auto& object = m_pObjects[objectIdx];

		if (object->GetIsSetForRemoval())  
		{
			// If the object has no parent, set its children's parent to nullptr
			if (object->GetParent() == nullptr) 
			{
				for (int idx = 0; idx < int(object->GetChildCount()); ++idx)
				{
					object->GetChildAt(idx)->SetParent(nullptr, true);
				}
			}
			else
			{
				for (int idx = 0; idx < int(object->GetChildCount()); ++idx) 
				{
					object->GetChildAt(idx)->SetParent(object->GetParent(), true);
				}
			}
			
			object.reset(); 
			Remove(std::move(object)); 
		}
	}
}

void Scene::Render() const
{
	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
}

std::string Scene::GetSceneName() const
{
	return m_Name;
}