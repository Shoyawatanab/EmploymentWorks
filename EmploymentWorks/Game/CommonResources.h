/*
	@file	CommonResources.h
	@brief	�V�[���֓n���A�Q�[�����Ŏg�p���鋤�ʃ��\�[�X
*/
#pragma once
#include "Game/Timer.h"
#include "Libraries/MyLib/Judgement.h"


// �O���錾
namespace DX
{
	class StepTimer;
	class DeviceResources;
}
namespace mylib
{
	class DebugString;
	class InputManager;
}


// ���ʃ��\�[�X
class CommonResources
{
private:
	// �󂯓n�����郊�\�[�X�ꗗ
	DX::StepTimer* m_stepTimer;

	DX::DeviceResources* m_deviceResources;

	DirectX::CommonStates* m_commonStates;

	mylib::DebugString* m_debugString;

	mylib::InputManager* m_inputManager;

	std::unique_ptr<Timer> m_timer;

	std::unique_ptr<mylib::Judgement> m_judgement;


public:
	CommonResources();
	~CommonResources() = default;

	void Initialize(
		DX::StepTimer* timer,
		DX::DeviceResources* dr,
		DirectX::CommonStates* commonStates,
		mylib::DebugString* debugString,
		mylib::InputManager* inputManager
	);

	// getter
	DX::StepTimer* GetStepTimer() const
	{
		return m_stepTimer;
	}

	DX::DeviceResources* GetDeviceResources() const
	{
		return m_deviceResources;
	}

	DirectX::CommonStates* GetCommonStates() const
	{
		return m_commonStates;
	}

	mylib::DebugString* GetDebugString() const
	{
		return m_debugString;
	}

	mylib::InputManager* GetInputManager() const
	{
		return m_inputManager;
	}



	Timer* GetTimer() const
	{
		return m_timer.get();
	}

	mylib::Judgement* GetJudgement() const
	{
		return m_judgement.get();
	}

};
