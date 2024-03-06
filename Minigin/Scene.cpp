#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update(float deltaTime)
{
	for (auto& object : m_objects)
	{
		object->Update(deltaTime);
	}

	for (auto& object : m_objects)
	{
		if (object->GetIsSetForRemoval()) 
		{
			// If the object has no parent, set its children's parent to nullptr
			if (object->GetParent() == nullptr) 
			{
				for (int idx = 0; idx < object->GetChildCount(); ++idx)
				{
					object->GetChildAt(idx)->SetParent(nullptr, true);
				}
			}
			else
			{
				for (int idx = 0; idx < object->GetChildCount(); ++idx) 
				{
					object->GetChildAt(idx)->SetParent(object->GetParent(), true);
				}
			}
			
			object.reset(); 
			Remove(object); 
		}
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

