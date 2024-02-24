#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include "Component.h"
#include "TransformComponent.h"

namespace dae
{
	class Texture2D;
	//class Component;

	// todo: this should become final.
	class GameObject
	{
	public:

		GameObject() = default;
		virtual ~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//todo : name parameter if used
		virtual void Update(float);
		virtual void Render() const;

		//void SetTexture(const std::string& filename);
		//void SetPosition(float x, float y);

		template<typename ComponentType>
		void AddComponent();

		template<typename ComponentType>
		void RemoveComponent();

		template<typename ComponentType>
		std::shared_ptr<ComponentType> GetComponent();

		template<typename ComponentType> 
		bool HasComponent();

	private:
		//shared pointers!!!
		std::vector<std::shared_ptr<Component> > m_pComponents{};

		std::unique_ptr<TransformComponent> m_pTransformComponent;
		//Transform m_Transform{}; 

		// todo: mmm, every gameobject has a texture? Is that correct?
		// No, not every GameObject has a texture
		// -> Add texture component
	};

	template<typename ComponentType>
	inline void GameObject::AddComponent()
	{
		m_pComponents.push_back(std::shared_ptr<ComponentType>);
	}

	template<typename ComponentType>
	inline void GameObject::RemoveComponent()
	{
		auto findComponent{ std::find(m_pComponents.begin(),m_pComponents.end(), std::shared_ptr<ComponentType>) };

		if (findComponent != m_pComponents.end())
		{
			m_pComponents.erase(findComponent);
		}
	}

	template<typename ComponentType>
	inline std::shared_ptr<ComponentType> GameObject::GetComponent()
	{
		/*for (int idx = 0; idx < m_pComponents.size(); ++idx)
		{
			if (ComponentType* componentType = dynamic_cast<ComponentType*>(m_pComponents[idx].get())) 
			{
				return std::make_unique<ComponentType>(componentType); 
			}
			else
			{
				return nullptr;
			}
		}
		return nullptr;*/

		auto findComponent{ std::find(m_pComponents.begin(),m_pComponents.end(), std::shared_ptr<ComponentType>) }; 

		if (findComponent != m_pComponents.end()) 
		{
			return findComponent;
		}
	}

	template<typename ComponentType>
	bool GameObject::HasComponent()
	{
		auto findComponent{ std::find(m_pComponents.begin(),m_pComponents.end(), std::shared_ptr<ComponentType>) }; 

		if (findComponent != m_pComponents.end()) 
		{
			return true;
		}

		return false;
	}
}
