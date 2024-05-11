#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <vector>
#include <string>
#include <SDL.h>

#include "Keyboard.h"

namespace dae
{
	class Keyboard::KeyboardImpl
	{
	public:
		KeyboardImpl();
		~KeyboardImpl();

		KeyboardImpl(const KeyboardImpl& other) = delete;
		KeyboardImpl(KeyboardImpl&& other) = delete;
		KeyboardImpl& operator=(const KeyboardImpl& other) = delete;
		KeyboardImpl& operator=(KeyboardImpl&& other) = delete;

		void Update();
		std::string GetPressedKey() const; 

		bool IsDownThisFrame(SDL_Scancode key) const;
		bool IsUpThisFrame(SDL_Scancode key) const;
		bool IsPressed(SDL_Scancode key) const;

	private:
		std::vector<Uint8> m_PreviousState;
		std::vector<Uint8> m_CurrentState;
	};

	//KEYBOARD CLASS
	dae::Keyboard::Keyboard() :
		m_pKeyboardImpl{ std::make_unique<KeyboardImpl>() }
	{
	}

	dae::Keyboard::~Keyboard()
	{
	}

	void dae::Keyboard::Update()
	{
		m_pKeyboardImpl->Update();
	}

	std::string Keyboard::GetPressedKey() const
	{
		return m_pKeyboardImpl->GetPressedKey();
	}

	bool Keyboard::IsDownThisFrame(SDL_Scancode key) const
	{
		return m_pKeyboardImpl->IsDownThisFrame(key); 
	}

	bool Keyboard::IsUpThisFrame(SDL_Scancode key) const
	{
		return m_pKeyboardImpl->IsUpThisFrame(key);
	}

	bool Keyboard::IsPressed(SDL_Scancode key) const
	{
		return m_pKeyboardImpl->IsPressed(key); 
	}

	//KEYBOARD IMPLEMENTATION CLASS
	Keyboard::KeyboardImpl::KeyboardImpl() :
		m_PreviousState(SDL_NUM_SCANCODES),
		m_CurrentState(SDL_NUM_SCANCODES)
	{
		for (int i = 0; i < SDL_NUM_SCANCODES; ++i)
		{
			m_PreviousState[i] = 0;
			m_CurrentState[i] = 0;
		}
	}

	Keyboard::KeyboardImpl::~KeyboardImpl()
	{
	}

	void Keyboard::KeyboardImpl::Update()
	{
		//Updates keyboard states
		SDL_PumpEvents();

		//Keep track of the previous state
		m_PreviousState = m_CurrentState;

		// Retrieve the current keyboard state directly into m_CurrentState
		int numKeysPressed{ 0 };
		const Uint8* state{ SDL_GetKeyboardState(&numKeysPressed) };

		for (int i = 0; i < numKeysPressed; ++i) 
		{
			m_CurrentState[i] = state[i]; 
		}
	}

	std::string Keyboard::KeyboardImpl::GetPressedKey() const
	{
		for (int i = 0; i < SDL_NUM_SCANCODES; ++i) 
		{
			if (m_CurrentState[i] && !m_PreviousState[i]) 
			{ 
				return SDL_GetScancodeName(static_cast<SDL_Scancode>(i)); 
			}
		}

		return "";
	}

	bool Keyboard::KeyboardImpl::IsDownThisFrame(SDL_Scancode key) const
	{
		return m_CurrentState[key] && !m_PreviousState[key]; 
	}

	bool Keyboard::KeyboardImpl::IsUpThisFrame(SDL_Scancode key) const
	{
		return !m_CurrentState[key] && m_PreviousState[key];
	}

	bool Keyboard::KeyboardImpl::IsPressed(SDL_Scancode key) const
	{
		return m_CurrentState[key];
	}
}