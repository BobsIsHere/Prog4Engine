#pragma once
#include <vector>
#include <memory>
#include <map>
#include "Command.h"
#include "Keyboard.h"
#include "Singleton.h"
#include "Controller.h"

namespace dae
{
	enum struct ButtonState
	{
		Is_Down,
		Is_Pressed,
		Is_Up
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		// Make Singleton template class a friend to access protected constructor and destructor
		friend class Singleton<InputManager>;
		
		bool ProcessInput(float deltaTime);

		void AddCommand(unsigned int controllerIdx, Controller::GamePad gamepadButton, ButtonState state, std::unique_ptr<Command> pCommand);
		void AddCommand(SDL_Scancode key, ButtonState state, std::unique_ptr<Command> pCommand);

	protected:
		InputManager();
		~InputManager();

	private:
		// Using a type alias to define a ControllerButton as a pair of unsigned integer and a Controller::GamePad
		using ControllerButton = std::pair<unsigned int, Controller::GamePad>; 
		// Using a type alias to define a ControllerButtonState as a pair of ControllerButton and a ButtonState
		using ControllerButtonState = std::pair<ControllerButton, ButtonState>;
		// Using a type alias to define a ControllerCommandsMap as a map of ControllerButtonState to a unique pointer of Command
		using ControllerCommandsMap = std::map<ControllerButtonState, std::unique_ptr<Command>>;
		
		// Using a type alias to define a KeyboardKey as a pair of SDL_Scancode and a ButtonState
		using KeyboardKey = std::pair<SDL_Scancode, ButtonState>;
		// Using a type alias to define a KeyboardCommands as a map of KeyboardKey to a unique pointer of Command
		using KeyboardCommandsMap = std::map<KeyboardKey, std::unique_ptr<Command>>;

		//Variables
		std::unique_ptr<Keyboard> m_pKeyboard;
		std::vector<std::unique_ptr<Controller> > m_pControllers;

		ControllerCommandsMap m_ControllerCommands;
		KeyboardCommandsMap m_KeyboardCommands;

		const int m_MaxControllers{ 2 };

		//Helper Functions
		void HandleControllerInput(float deltaTime);
		void HandleKeyboardInput(float deltaTime);
	};
}
