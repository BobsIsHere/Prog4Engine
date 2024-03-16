#pragma once
#include <memory>

namespace dae 
{
	class Controller final
	{
	public:
		enum struct GamePad
		{
			Dpad_Up		   = 0x0001,
			Dpad_Down	   = 0x0002,
			Dpad_Left	   = 0x0004,
			Dpad_Right	   = 0x0008,
			Start		   = 0x0010,
			Back		   = 0x0020,
			Left_Thumb	   = 0x0040,
			Right_Thumb    = 0x0080,
			Left_Shoulder  = 0x0100,
			Right_Shoulder = 0x0200,
			A			   = 0x1000,
			B			   = 0x2000,
			X			   = 0x4000,
			Y			   = 0x8000
		};

		enum struct AmountOfControllers
		{
			One,
			Two
		};

		explicit Controller(unsigned int controllerIdx);
		~Controller();
		
		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;

		void Update();

		bool IsDownThisFrame(GamePad button) const;
		bool IsUpThisFrame(GamePad button) const;
		bool IsPressed(GamePad button) const; 

		unsigned int GetControllerIdx() const;

		bool GetIsFirstController() const;

		void SetIsFirstController(bool setController);

	private:
		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_pControllerImpl;
	};
}