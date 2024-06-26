#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "Component.h"
#include "DeltaTime.h"
#include "TransformComponent.h"

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:

		GameObject(const std::string& objectTypeID = "");
		virtual ~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
		
		virtual void Update();
		virtual void Render() const;

		void UpdateWorldPosition();

		void SetLocalPosition(float x, float y);
		void SetLocalPosition(glm::vec3 pos);
		void SetParent(GameObject* pParent, bool keepWorldPosition);
		void SetPositionDirty();
		void SetForRemoval();
		void SetObjectTypeIdentifier(const std::string m_ObjectTypeIdentifier);

		TransformComponent& GetTransformComponent() const;
		const glm::vec3& GetWorldPosition(); 
		const glm::vec3& GetLocalPosition();

		GameObject* GetParent() const;
		GameObject* GetChildAt(unsigned int index) const;
		size_t GetChildCount() const;
		bool GetIsSetForRemoval() const;
		std::string GetObjectTypeIdentifier() const;

		bool IsChild(const GameObject* pChild) const;

		// TEMPLATED FUNCTIONS
		template<typename ComponentType>
		void AddComponent(std::shared_ptr<ComponentType> comp);

		template<typename ComponentType>
		void RemoveComponent();

		template<typename ComponentType>
		ComponentType* GetComponent();

		template<typename ComponentType> 
		bool HasComponent();

	private:
		//FUNCTIONS
		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);

		//VARIABLES
		bool m_IsSetForRemoval;
		bool m_IsPositionDirty;

		std::vector<std::shared_ptr<Component> > m_pComponents{};
		std::unique_ptr<TransformComponent> m_pTransformComponent{};

		GameObject* m_pParent; 
		std::vector<GameObject*> m_pChildren;

		std::string m_ObjectTypeIdentifier; 
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
	inline ComponentType* GameObject::GetComponent()
	{
		auto findComponent = std::find_if(m_pComponents.begin(), m_pComponents.end(), [](const std::shared_ptr<Component>& ptr)
		{
				return dynamic_cast<ComponentType*>(ptr.get()) != nullptr;
		});

		if (findComponent != m_pComponents.end())
		{
			return dynamic_cast<ComponentType*>((*findComponent).get());  
		}

		// Return nullptr if component is not found
		return nullptr;
	}

	template<typename ComponentType>
	bool GameObject::HasComponent()
	{
		auto findComponent = std::find_if(m_pComponents.begin(), m_pComponents.end(), [](const std::shared_ptr<Component>& ptr)  
		{
			return dynamic_cast<ComponentType*>(ptr.get()) != nullptr; 
		}); 

		if (findComponent != m_pComponents.end()) 
		{
			return true;
		}

		return false; 
	} 
} 