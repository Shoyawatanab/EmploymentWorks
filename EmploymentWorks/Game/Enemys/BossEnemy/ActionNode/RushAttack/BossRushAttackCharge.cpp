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

IBehaviorNode::State BossRushAttackCharge::Update(const float& elapsedTime)
{
	//���Ԃ̓A�j���[�V�����ƍ��킹��
	if (m_time >= 1.5f)
	{

		

	}

	
	m_time += elapsedTime;

	return IBehaviorNode::State::Runngin;

}



void BossRushAttackCharge::Enter()
{

	m_bossEnemy->ChangeAnimation("JumpCharge");
	m_time = 0;

	Vector3 pos = m_bossEnemy->GetPosition();

	pos.y = 0.1f;

	EventParams::CreateHitEffectDatas aa = {  pos, Vector3(5,5,5)};

	Messenger::Notify(EventParams::EventType::CreateChageEffect, &aa);


}

void BossRushAttackCharge::Exit()
{
}
