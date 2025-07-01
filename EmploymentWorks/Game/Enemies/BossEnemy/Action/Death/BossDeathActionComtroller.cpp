/*
	@file	BossDeathActionComtroller.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "BossDeathActionComtroller.h"
#include "GameBase/Common/Commons.h"
#include "Game/Enemies/BossEnemy/Action/Death/BossDeathAction.h"
#include "Game/Enemies/BossEnemy/Action/Death/BossDeathEndAction.h"




/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="own">���L��</param>
/// <param name="target">�^�[�Q�b�g</param>
BossDeathActionComtroller::BossDeathActionComtroller(BossEnemy* bossEnemy)
{

	m_idle = std::make_unique<BossDeathAction>();
	m_end = std::make_unique<BossDeathEndAction>(bossEnemy);

	AddAction(
		{
			m_idle.get()
			,m_end.get()
		}
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossDeathActionComtroller::~BossDeathActionComtroller()
{
	// do nothing.
}


