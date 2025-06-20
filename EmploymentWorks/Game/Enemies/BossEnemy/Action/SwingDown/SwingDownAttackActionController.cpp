/*
	@file	SwingDownAttackActionController.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "SwingDownAttackActionController.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Params.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">�o�ߎ���</param>
/// <param name="owner">���L��</param>
SwingDownAttackActionController::SwingDownAttackActionController(Actor* owner)
	:
	m_commonResources{}
{

	//�e��Ԃ̍쐬
	m_raisePhase = std::make_unique<SwingDownAttackRaisePhase>(this, owner);

	m_swingPhase = std::make_unique<SwingDownAttackSwingPhase>(this, owner);


	//m_currentState->Enter();


	//���쏇�ɒǉ�
	AddAction({
		m_raisePhase.get()
		,m_swingPhase.get()
		});


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SwingDownAttackActionController::~SwingDownAttackActionController()
{
	// do nothing.
}







