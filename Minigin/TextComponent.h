#pragma once
#include <string>
#include "UpdateComponent.h"

namespace dae
{
	class Font;
	class Texture2D;

	class TextComponent final : public UpdateComponent
	{
	public:
		TextComponent(std::weak_ptr<GameObject> pGameObject, std::shared_ptr<Font> pFont);
		virtual ~TextComponent();

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		virtual void Update(float deltaTime) override;

		void SetText(const std::string& text);

	private:
		std::shared_ptr<Font> m_pFont;
		std::string m_Text;

		bool m_NeedsUpdate;
	};
}