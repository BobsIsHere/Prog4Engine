#include <stdexcept>
#include <SDL_ttf.h>
#include "GameObject.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

dae::TextComponent::TextComponent(GameObject* pGameObject) :
	UpdateComponent{ pGameObject },
	m_pFont{},
	m_Text{},
	m_NeedsUpdate{ false }
{
	if (!pGameObject->HasComponent<TextureComponent>())
	{
		pGameObject->AddComponent<TextureComponent>(std::make_unique<TextureComponent>(pGameObject));
	}

	m_pTextureComponent = pGameObject->GetComponent<TextureComponent>();
}

dae::TextComponent::~TextComponent()
{
}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTextureComponent->SetTexture(std::make_shared<Texture2D>(texture));
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetFont(const std::shared_ptr<Font>& font)
{
	m_pFont = font;
}
