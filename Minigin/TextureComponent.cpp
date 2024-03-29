#include "ResourceManager.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include <SDL.h>

dae::TextureComponent::TextureComponent(GameObject* pGameObject) :
	RenderComponent{ pGameObject },
	m_pTexture{}
{
	
}

dae::TextureComponent::~TextureComponent()
{
}

void dae::TextureComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		const auto& position = GetGameObject()->GetTransformComponent().GetWorldPosition(); 
		Renderer::GetInstance().RenderTexture(*m_pTexture, position.x, position.y); 
	}
}

void dae::TextureComponent::RenderGui()
{
}

void dae::TextureComponent::SetTexture(std::string fileName)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
}

void dae::TextureComponent::SetTexture(const std::shared_ptr<Texture2D>& pTexture)
{
	if (pTexture != nullptr)
	{
		m_pTexture = pTexture;
	}
}
