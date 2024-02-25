#include <string>
#include "GameObject.h"
#include "Component.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::GameObject()
{
	m_pTransformComponent = std::make_unique<TransformComponent>(std::shared_ptr<GameObject>());
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

void dae::GameObject::SetPosition(float x, float y)
{
	m_pTransformComponent->SetPosition(x, y);
}

dae::TransformComponent& dae::GameObject::GetTransformComponent()
{
	return *m_pTransformComponent;
}
