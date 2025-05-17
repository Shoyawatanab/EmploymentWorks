/*
	@file	BossJumpAttackCharge.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "BossJumpAttackCharge.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Enemys/BossEnemy/BossEnemy.h"
#include "Game/Player/Player.h"
#include "Game/Enemys/BossEnemy/ActionNode/JumpAttack/BossJumpAttackAction.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
BossJumpAttackCharge::BossJumpAttackCharge(CommonResources* resources
	,BossJumpAttackAction* parent
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
BossJumpAttackCharge::~BossJumpAttackCharge()
{
	// do nothing.
}

void BossJumpAttackCharge::Initialize()
{


}

BossJumpAttackCharge::ActionState BossJumpAttackCharge::Update(const float& elapsedTime)
{
	//���Ԃ̓A�j���[�V�����ƍ��킹��
	if (m_time >= 1.5f)
	{
		return ActionState::End;
	}

	
	m_time += elapsedTime;

	return ActionState::Running;

}






void BossJumpAttackCharge::Enter()
{

	m_bossEnemy->ChangeAnimation("JumpCharge");
	m_time = 0;

	Vector3 pos = m_bossEnemy->GetPosition();

	pos.y = 0.1f;

	Vector3 scale = Vector3(5, 5, 5);

	UnknownDataThree aa = {  static_cast<void*>(& pos), static_cast<void*>(&scale)};

	Messenger::GetInstance()->Notify(GameMessageType::CreateChageEffect, &aa);


}

void BossJumpAttackCharge::Exit()
{
}
