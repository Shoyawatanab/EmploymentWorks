/*
	@file	IdleingAction.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "IdleingAction.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Params.h"
#include "Game/Observer/Messenger.h"

#include "IdleingAction.h"
#include "Game/Entities/CharacterEntity.h"




/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="own">���L��</param>
/// <param name="target">�^�[�Q�b�g</param>
IdleingAction::IdleingAction(CommonResources* resources
	, CharacterEntity* own
	)
	:
	m_commonResources{resources}
	,m_own{own}
	,m_time{}
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
IdleingAction::~IdleingAction()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
void IdleingAction::Initialize()
{

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�p�����I����</returns>
IdleingAction:: ActionState IdleingAction::Update(const float& elapsedTime)
{

	return ActionState::END;

}


/// <summary>
/// ��Ԃɓ�������
/// </summary>
void IdleingAction::Enter()
{

	m_own->ChangeAnimation("Idel");

	m_time = 0;
}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void IdleingAction::Exit()
{
}
