/*
	@file	IdleingActionComtroller.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "IdleingActionComtroller.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "IdleingActionComtroller.h"
#include "Game/Entities/CharacterEntity.h"




/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="own">���L��</param>
/// <param name="target">�^�[�Q�b�g</param>
IdleingActionComtroller::IdleingActionComtroller(CommonResources* resources
	, CharacterEntity* own
	)
	:
	m_commonResources{resources}
	,m_own{own}
{

	m_idle = std::make_unique<IdleingAction>(m_commonResources,m_own);

	//���쏇�ɒǉ�
	ActionStateController::Initialize({ 
		m_idle.get()
		});

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
IdleingActionComtroller::~IdleingActionComtroller()
{
	// do nothing.
}


