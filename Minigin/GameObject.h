#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include "Component.h"
#include "TransformComponent.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject
	{
	public:

		GameObject();
		virtual ~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//todo : name parameter if used
		virtual void Update(float);
		virtual void Render() const;

		void SetPosition(float x, float y);

		TransformComponent& GetTransformComponent();

		template<typename ComponentType>
		void AddComponent(std::shared_ptr<ComponentType> comp);

		template<typename ComponentType>
		void RemoveComponent();

		template<typename ComponentType>
		std::shared_ptr<ComponentType> GetComponent();

		template<typename ComponentType> 
		bool HasComponent();

	private:
		//shared pointers!!!
		std::vector<std::shared_ptr<Component> > m_pComponents{};

		std::unique_ptr<TransformComponent> m_pTransformComponent{};

		// todo: mmm, every gameobject has a texture? Is that correct?
		// No, not every GameObject has a texture
		// -> Add texture component
	};

	template<typename ComponentType>
	inline void GameObject::AddComponent(std::shared_ptr<ComponentType> comp)
	{
		static_assert(std::is_base_of<Component, ComponentType>::value, "This item must be of a derived class of Component");
		m_pComponents.push_back(std::move(comp));
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

		auto findComponent = std::find_if(m_pComponents.begin(), m_pComponents.end(), [](const std::shared_ptr<Component>& ptr)   
		{
			return std::dynamic_pointer_cast<ComponentType>(ptr) != nullptr;
		});

		if (findComponent != m_pComponents.end())
		{
			return std::dynamic_pointer_cast<ComponentType>(*findComponent);
		}

		// Return nullptr if component is not found
		return nullptr;
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