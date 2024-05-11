#pragma once
#include <memory>

namespace dae
{
	class Keyboard final
	{
	public:
		explicit Keyboard();
		~Keyboard();

		Keyboard(const Keyboard& other) = delete;
		Keyboard(Keyboard&& other) = delete;
		Keyboard& operator=(const Keyboard& other) = delete;
		Keyboard& operator=(Keyboard&& other) = delete;

		void Update();
		std::string GetPressedKey() const;

		bool IsDownThisFrame(SDL_Scancode key) const;
		bool IsUpThisFrame(SDL_Scancode key) const;
		bool IsPressed(SDL_Scancode key) const;

	private:
		class KeyboardImpl;
		std::unique_ptr<KeyboardImpl> m_pKeyboardImpl;
	};
}