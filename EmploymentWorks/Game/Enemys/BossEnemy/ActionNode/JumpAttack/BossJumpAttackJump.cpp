/*
	@file	BossJumpAttackJump.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "BossJumpAttackJump.h"
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
#include "BossJumpAttackAction.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
BossJumpAttackJump::BossJumpAttackJump(CommonResources* resources
	,BossJumpAttackAction* parent
	,BossEnemy* bossenemy
	, Player* player)
	:
	m_commonResources{resources}
	,m_bossEnemy{bossenemy}
	,m_player{player}
	,m_parent{parent}
	,m_jumpDirection{}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossJumpAttackJump::~BossJumpAttackJump()
{
	// do nothing.
}

void BossJumpAttackJump::Initialize()
{



}

BossJumpAttackJump::ActionState BossJumpAttackJump::Update(const float& elapsedTime)
{


	Vector3 velocity = m_bossEnemy->GetVelocity();

	velocity.x = m_jumpDirection.x * elapsedTime * BossJumpAttackAction::MOVESPEED;

	velocity.z = m_jumpDirection.z * elapsedTime * BossJumpAttackAction::MOVESPEED;

	m_bossEnemy->SetVelocity(velocity);

	if (m_bossEnemy->GetIsGrounded())
	{
		return ActionState::End;
	}

	return ActionState::Running;
}





void BossJumpAttackJump::Enter()
{

	Vector3 velocity = m_bossEnemy->GetVelocity();

	velocity.y += BossJumpAttackAction::JUMPPOWER;

	m_bossEnemy->SetVelocity(velocity);


	Vector3 bossPos = m_bossEnemy->GetPosition();

	Vector3 playerPos = m_player->GetPosition();


	//���������߂�
	m_jumpDirection = playerPos - bossPos;
	//���K��
	m_jumpDirection.Normalize();


}

void BossJumpAttackJump::Exit()
{

	m_bossEnemy->ChangeAnimation("Idel");

	Vector3 pos = m_bossEnemy->GetPosition();

	pos.y = 0.1f;

	Messenger::GetInstance()->Notify(MessageType::CreateParticle, &pos);

	m_bossEnemy->SetVelocity(Vector3::Zero);

}
