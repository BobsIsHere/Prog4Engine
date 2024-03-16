#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <XInput.h>
#include "Controller.h"

#pragma comment(lib, "xinput.lib")

namespace dae
{
	class Controller::ControllerImpl
	{
	public:
		ControllerImpl(unsigned int controllerIdx);
		~ControllerImpl();

		ControllerImpl(const ControllerImpl& other) = delete;
		ControllerImpl(ControllerImpl&& other) = delete;
		ControllerImpl& operator=(const ControllerImpl& other) = delete;
		ControllerImpl& operator=(ControllerImpl&& other) = delete;

		void Update(); 
		
		bool IsDownThisFrame(unsigned int button) const;
		bool IsUpThisFrame(unsigned int button) const;
		bool IsPressed(unsigned int button) const;

		unsigned int GetControllerIdx() const;
		
		bool GetIsFirstController() const;

		void SetIsFirstController(bool setController);

	private:
		int m_ButtonsPressedThisFrame;
		int m_ButtonsReleasedThisFrame;

		unsigned int m_ControllerIdx;
		bool m_IsFirstController;

		XINPUT_STATE m_PreviousState;
		XINPUT_STATE m_CurrentState;
	};

	//CONTROLLER CLASS
	dae::Controller::Controller(unsigned int controllerIdx) :
		m_pControllerImpl{}
	{
		m_pControllerImpl = std::make_unique<ControllerImpl>(controllerIdx);
	}

	Controller::~Controller()
	{
	}

	void Controller::Update()
	{
		m_pControllerImpl->Update(); 
	}

	bool Controller::IsDownThisFrame(GamePad button) const
	{
		return m_pControllerImpl->IsDownThisFrame(static_cast<unsigned int>(button));
	}

	bool Controller::IsUpThisFrame(GamePad button) const
	{
		return m_pControllerImpl->IsUpThisFrame(static_cast<unsigned int>(button));
	}

	bool Controller::IsPressed(GamePad button) const
	{
		return m_pControllerImpl->IsPressed(static_cast<unsigned int>(button));
	}

	unsigned int dae::Controller::GetControllerIdx() const
	{
		return m_pControllerImpl->GetControllerIdx();
	}

	bool dae::Controller::GetIsFirstController() const
	{
		return m_pControllerImpl->GetIsFirstController();
	}

	void Controller::SetIsFirstController(bool setController)
	{
		m_pControllerImpl->SetIsFirstController(setController);
	}

	//CONTROLLER IMPLEMENTATION
	Controller::ControllerImpl::ControllerImpl(unsigned int controllerIdx) :
		m_ButtonsPressedThisFrame{},
		m_ButtonsReleasedThisFrame{},
		m_IsFirstController{  },
		m_PreviousState{},
		m_CurrentState{},
		m_ControllerIdx{ controllerIdx }
	{
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE)); 
	}

	Controller::ControllerImpl::~ControllerImpl() 
	{
	}

	void Controller::ControllerImpl::Update()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE)); 
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE)); 
		XInputGetState(static_cast<DWORD>(m_IsFirstController), &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons); 
	}

	bool Controller::ControllerImpl::IsDownThisFrame(unsigned int button) const
	{
		return m_ButtonsPressedThisFrame & button; 
	}

	bool Controller::ControllerImpl::IsUpThisFrame(unsigned int button) const
	{
		return m_ButtonsReleasedThisFrame & button;
	}

	bool Controller::ControllerImpl::IsPressed(unsigned int button) const
	{
		return m_CurrentState.Gamepad.wButtons & button;
	}

	unsigned int dae::Controller::ControllerImpl::GetControllerIdx() const
	{
		return m_ControllerIdx;
	}

	bool dae::Controller::ControllerImpl::GetIsFirstController() const
	{
		return m_IsFirstController;
	}

	void dae::Controller::ControllerImpl::SetIsFirstController(bool setController)
	{
		m_IsFirstController = setController;
	}
}