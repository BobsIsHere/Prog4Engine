#pragma once
#include "RenderComponent.h"
#include <glm/vec2.hpp>

struct SDL_Texture; 
namespace dae
{
	class Texture2D;
	class GameObject;

	class TextureComponent final : public RenderComponent
	{
	public:
		TextureComponent(GameObject* pGameObject);
		virtual ~TextureComponent();

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		virtual void Render() const override;
		void SetTexture(std::string fileName);
		void SetTexture(const std::shared_ptr<Texture2D>& pTexture);

	private:
		std::shared_ptr<Texture2D> m_pTexture; 
	};
}
