#include <string>
#include "GameObject.h"
#include "Component.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::GameObject() :
	m_IsSetForRemoval{},
	m_IsPositionDirty{ true },
	m_pParent{}
{
	m_pTransformComponent = std::make_unique<TransformComponent>(this);
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime)
{
	for (size_t idx = 0; idx < m_pComponents.size(); ++idx)
	{
		m_pComponents[idx]->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (size_t idx = 0; idx < m_pComponents.size(); ++idx)
	{
		m_pComponents[idx]->Render();
	}
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_IsPositionDirty)
	{
		if (m_pParent == nullptr)
		{
			m_pTransformComponent->SetWorldPosition(m_pTransformComponent->GetLocalPosition().x, m_pTransformComponent->GetLocalPosition().y);
		}
		else
		{
			m_pTransformComponent->SetWorldPosition(m_pParent->GetWorldPosition().x + m_pTransformComponent->GetLocalPosition().x, 
													m_pParent->GetWorldPosition().y + m_pTransformComponent->GetLocalPosition().y); 
		}
	}

	m_IsPositionDirty = false;
}

void dae::GameObject::SetLocalPosition(float x, float y)
{
	m_pTransformComponent->SetLocalPosition(x, y);
	SetPositionDirty(); 
}

void dae::GameObject::SetParent(GameObject* pParent, bool keepWorldPosition)
{
	if (pParent->IsChild(this) || m_pParent == pParent || pParent == this) 
	{
		return;
	}

	if (pParent == nullptr)
	{
		SetLocalPosition(GetWorldPosition().x, GetWorldPosition().y);
	}
	else
	{
		if (keepWorldPosition)
		{
			SetLocalPosition(GetWorldPosition().x - pParent->GetWorldPosition().x, GetWorldPosition().y - pParent->GetWorldPosition().y);
		}

		SetPositionDirty();
	}

	if (m_pParent)
	{
		m_pParent->RemoveChild(this);
	}

	m_pParent = pParent;

	if (m_pParent)
	{
		m_pParent->AddChild(this);
	}
}

void dae::GameObject::SetPositionDirty()
{
	m_IsPositionDirty = true;

	for (auto& child : m_pChildren)
	{
		child->SetPositionDirty(); 
	}
}

void dae::GameObject::SetForRemoval()
{
	m_IsSetForRemoval = true;
}

void dae::GameObject::AddChild(GameObject* pChild)
{
	m_pChildren.emplace_back(pChild);
}

void dae::GameObject::RemoveChild(GameObject* pChild)
{
	m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), pChild), m_pChildren.end());
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	UpdateWorldPosition();
	return m_pTransformComponent->GetWorldPosition();
}

dae::TransformComponent& dae::GameObject::GetTransformComponent() const
{
	return *m_pTransformComponent;
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}

dae::GameObject* dae::GameObject::GetChildAt(unsigned int index) const
{
	if (index < GetChildCount())
	{
		return m_pChildren[index];
	}
	return nullptr;
}

size_t dae::GameObject::GetChildCount() const
{
	return m_pChildren.size();
}

bool dae::GameObject::GetIsSetForRemoval()
{
	return m_IsSetForRemoval;
}

bool dae::GameObject::IsChild(const GameObject* pChild) const
{
	for (const auto& child : m_pChildren) 
	{
		if (child == pChild)  
		{
			return true;
		}
	}
	return false;
}