/*
	@file	CommonResources.h
	@brief	�V�[���֓n���A�Q�[�����Ŏg�p���鋤�ʃ��\�[�X
*/
#pragma once
#include "Libraries/WataLib/Singleton.h"

class Fade;
class Score;

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

namespace WataLib
{
	class GameResources;
}

// ���ʃ��\�[�X
class CommonResources : public Singleton<CommonResources>
{
	friend class Singleton<CommonResources>;

private:
	// �󂯓n�����郊�\�[�X�ꗗ
	DX::StepTimer* m_stepTimer;

	DX::DeviceResources* m_deviceResources;

	DirectX::CommonStates* m_commonStates;

	mylib::DebugString* m_debugString;

	mylib::InputManager* m_inputManager;

	Fade* m_fade;

	Score* m_score;

	WataLib::GameResources* m_gameResources;

public:
	CommonResources();
	~CommonResources() = default;

	void Initialize(
		DX::StepTimer* timer,
		DX::DeviceResources* dr,
		DirectX::CommonStates* commonStates,
		mylib::DebugString* debugString,
		mylib::InputManager* inputManager,
		Fade* fade,
		Score* score,
		WataLib::GameResources* gameResources
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

	Fade* GetFade() const
	{
		return m_fade;
	}

	Score* GetScore() const
	{
		return m_score;
	}

	WataLib::GameResources* GetGameResources() const
	{
		return m_gameResources;
	}

};
