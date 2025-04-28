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

#include "Game/Enemys/BossEnemy/BossEnemy.h"
#include "Game/Player/Player.h"
#include "Game/Enemys/BossEnemy/ActionNode/RushAttack/BossRushAttackAction.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
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

void BossRushAttackCharge::Initialize()
{
}

BossRushAttackCharge::ActionState BossRushAttackCharge::Update(const float& elapsedTime)
{
	//���Ԃ̓A�j���[�V�����ƍ��킹��
	if (m_time >= 1.5f)
	{

		

	}

	
	m_time += elapsedTime;

	return ActionState::Running;
}



void BossRushAttackCharge::Enter()
{

	m_bossEnemy->ChangeAnimation("JumpCharge");
	m_time = 0;

	Vector3 pos = m_bossEnemy->GetPosition();

	pos.y = 0.1f;

	Vector3 scale = Vector3(5, 5, 5);


	UnknownDataThree aa = { static_cast<void*>(&pos), static_cast<void*>(&scale) };

	Messenger::GetInstance()->Notify(MessageType::CreateChageEffect, &aa);


}

void BossRushAttackCharge::Exit()
{
}
