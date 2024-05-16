#pragma once
#include <SDL.h>
#include <memory>
#include <vector>
#include "Singleton.h"

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float scale) const;

		SDL_Renderer* GetSDLRenderer() const;
		SDL_Window* GetWindow() const;

		const SDL_Color& GetBackgroundColor() const { return m_pClearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_pClearColor = color; }

	private:
		SDL_Renderer* m_pRenderer{};
		SDL_Window* m_pWindow{};
		SDL_Color m_pClearColor{}; 
	};
}

