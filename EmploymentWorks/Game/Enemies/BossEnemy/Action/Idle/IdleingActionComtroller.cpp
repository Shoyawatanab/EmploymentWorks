/*
	@file	IdleingActionComtroller.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "IdleingActionComtroller.h"
#include "GameBase/Common/Commons.h"
#include "Game/Enemies/BossEnemy/Action/Idle/IdleingAction.h"




/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="own">���L��</param>
/// <param name="target">�^�[�Q�b�g</param>
IdleingActionComtroller::IdleingActionComtroller()
{

	m_idle = std::make_unique<IdleingAction>();

	AddAction(
		{
			m_idle.get()
		}
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
IdleingActionComtroller::~IdleingActionComtroller()
{
	// do nothing.
}


