#include <SDL.h>
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"

dae::InputManager::InputManager() :
	m_pKeyboard{},
	m_pControllers{}
{
	m_pKeyboard = std::make_unique<Keyboard>();

	for (int idx = 0; idx < m_MaxControllers; ++idx)
	{
		m_pControllers.push_back(std::make_unique<Controller>(idx));
	}
}

dae::InputManager::~InputManager()
{
}

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) 
		{
			return false;
		}
	}

	HandleControllerInput();
	HandleKeyboardInput();

	return true;
}

void dae::InputManager::AddControllerCommand(unsigned int controllerIdx, Controller::GamePad gamepadButton, ButtonState state, std::unique_ptr<Command> pCommand)
{
	ControllerButton buttonPair{ std::make_pair(controllerIdx, gamepadButton) };
	ControllerButtonState buttonStatePair{ std::make_pair(buttonPair, state) };
	m_ControllerCommands.emplace(std::make_pair(buttonStatePair, std::move(pCommand)));
}

void dae::InputManager::AddKeyboardCommand(SDL_Scancode key, ButtonState state, std::unique_ptr<Command> pCommand)
{
	KeyboardKey keyPair{ std::make_pair(key, state) };
	m_KeyboardCommands.emplace(std::make_pair(keyPair, std::move(pCommand)));
}

void dae::InputManager::RemoveControllerCommand(unsigned int controllerIdx, Controller::GamePad gamepadButton, ButtonState state)
{
	ControllerButton buttonPair{ std::make_pair(controllerIdx, gamepadButton) };
	ControllerButtonState buttonStatePair{ std::make_pair(buttonPair, state) };
	m_ControllerCommands.erase(buttonStatePair);
}

void dae::InputManager::RemoveKeyboardCommand(SDL_Scancode key, ButtonState state)
{
	KeyboardKey keyPair{ std::make_pair(key, state) };
	m_KeyboardCommands.erase(keyPair);
}

bool dae::InputManager::IsKeyDown(SDL_Scancode key) const
{
	return m_pKeyboard->IsDownThisFrame(key);
}

std::string dae::InputManager::GetPressedKey() const
{
	return m_pKeyboard->GetPressedKey();
}

void dae::InputManager::HandleControllerInput()
{
	//auto& -> avoid copying unique_ptr instances, invalid due to non-copyable 
	for (auto& controller : m_pControllers)
	{
		controller->Update();

		for (const auto& command : m_ControllerCommands)
		{
			//checking if this command is connectedto the correct controller
			if (command.first.first.first == controller->GetControllerIdx())
			{
				switch (command.first.second)
				{
				case ButtonState::Is_Down:
					if (controller->IsDownThisFrame(command.first.first.second))
					{
						command.second->Execute();
					}
					break;

				case ButtonState::Is_Pressed:
					if (controller->IsPressed(command.first.first.second))
					{
						command.second->Execute();
					}
					break;

				case ButtonState::Is_Up:
					if (controller->IsUpThisFrame(command.first.first.second))
					{
						command.second->Execute();
					}
					break;
				}
			}
		}
	}
}

void dae::InputManager::HandleKeyboardInput()
{
	m_pKeyboard->Update();

	for (const auto& command : m_KeyboardCommands)
	{
		switch (command.first.second)
		{
		case ButtonState::Is_Down:
			if (m_pKeyboard->IsDownThisFrame(command.first.first))
			{
				command.second->Execute();
			}
			break;

		case ButtonState::Is_Pressed:
			if (m_pKeyboard->IsPressed(command.first.first))
			{
				command.second->Execute();
			}
			break;

		case ButtonState::Is_Up:
			if (m_pKeyboard->IsUpThisFrame(command.first.first))
			{
				command.second->Execute();
			}
			break;
		}
	}
}
