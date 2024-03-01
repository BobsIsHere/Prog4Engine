#pragma once
#include <string>
#include "UpdateComponent.h"
#include "TextureComponent.h"
#include "Font.h"

namespace dae
{
	class Font;
	class Texture2D;

	class TextComponent final : public UpdateComponent
	{
	public:
		TextComponent(GameObject* pGameObject);
		virtual ~TextComponent();

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		virtual void Update(float deltaTime) override;

		void SetText(const std::string& text);
		void SetFont(const std::shared_ptr<Font>& font);

	private:
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<TextureComponent> m_pTextureComponent;

		std::string m_Text;

		bool m_NeedsUpdate;
	};
}