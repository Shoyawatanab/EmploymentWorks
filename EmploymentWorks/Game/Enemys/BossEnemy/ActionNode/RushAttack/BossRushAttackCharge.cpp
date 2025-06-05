/*
	@file	BossRushAttackCharge.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "BossRushAttackCharge.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Player/Player.h"
#include "Game/Enemys/BossEnemy/ActionNode/RushAttack/BossRushAttackAction.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="parent">�R���g���[���[</param>
/// <param name="bossenemy">���L��</param>
/// <param name="player">�v���C��</param>
BossRushAttackCharge::BossRushAttackCharge(CommonResources* resources
	, BossRushAttackAction* parent
	,BossEnemy* bossenemy
	, Player* player)
	:
	m_commonResources{resources}
	,m_bossEnemy{bossenemy}
	,m_player{player}
	,m_parent{parent}
	,m_time{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossRushAttackCharge::~BossRushAttackCharge()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
void BossRushAttackCharge::Initialize()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�p�����I����</returns>
BossRushAttackCharge::ActionState BossRushAttackCharge::Update(const float& elapsedTime)
{
	//���Ԃ̓A�j���[�V�����ƍ��킹��
	if (m_time >= CHARGE_TIME)
	{

		return ActionState::END;

	}

	
	m_time += elapsedTime;

	return ActionState::RUNNING;
}


/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BossRushAttackCharge::Enter()
{

	//m_bossEnemy->ChangeAnimation("JumpCharge");
	//m_time = 0;

	//Vector3 pos = m_bossEnemy->GetPosition();

	//pos.y = 0.1f;

	//Vector3 scale = EFFECTE_SCALE;


	//UnknownDataThree aa = { static_cast<void*>(&pos), static_cast<void*>(&scale) };

	//Messenger::GetInstance()->Notify(GamePlayMessageType::CREATE_CHAGE_EFFECT, &aa);


}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BossRushAttackCharge::Exit()
{
}
