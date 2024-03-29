#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "Component.h"
#include "TransformComponent.h"

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:

		GameObject();
		virtual ~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
		
		virtual void Update(float deltaTime);
		virtual void Render() const;

		void UpdateWorldPosition();

		void SetLocalPosition(float x, float y);
		void SetLocalPosition(glm::vec3 pos);
		void SetParent(GameObject* pParent, bool keepWorldPosition);
		void SetPositionDirty();
		void SetForRemoval();

		TransformComponent& GetTransformComponent() const;
		GameObject* GetParent() const;
		GameObject* GetChildAt(unsigned int index) const;
		size_t GetChildCount() const;
		bool GetIsSetForRemoval() const;

		bool IsChild(const GameObject* pChild) const;

		// TEMPLATED FUNCTIONS
		template<typename ComponentType>
		void AddComponent(std::shared_ptr<ComponentType> comp);

		template<typename ComponentType>
		void RemoveComponent();

		template<typename ComponentType>
		std::shared_ptr<ComponentType> GetComponent();

		template<typename ComponentType> 
		bool HasComponent();

	private:
		//FUNCTIONS
		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);
		
		const glm::vec3& GetWorldPosition();

		//VARIABLES
		bool m_IsSetForRemoval;
		bool m_IsPositionDirty;

		std::vector<std::shared_ptr<Component> > m_pComponents{};
		std::unique_ptr<TransformComponent> m_pTransformComponent{};

		GameObject* m_pParent; 
		std::vector<GameObject*> m_pChildren;
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
		/*auto findComponent{ std::find(m_pComponents.begin(),m_pComponents.end(), std::shared_ptr<ComponentType>()) };  

		if (findComponent != m_pComponents.end())  
		{
			return true;
		}

		return false;*/

		ComponentType* temp{};
		for (size_t idx{}; idx < m_pComponents.size(); idx++)
		{
			temp = dynamic_cast<ComponentType*>(m_pComponents[idx].get()); 
			if (temp != nullptr)
			{
				return true;
			}
		}
		return false;
	}
}