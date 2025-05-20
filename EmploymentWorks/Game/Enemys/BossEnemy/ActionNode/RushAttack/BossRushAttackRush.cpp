/*
	@file	BossRushAttackRush.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "BossRushAttackRush.h"
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


using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
BossRushAttackRush::BossRushAttackRush(CommonResources* resources
	, BossRushAttackAction* parent
	,BossEnemy* bossenemy
	, Player* player)
	:
	m_commonResources{resources}
	,m_bossEnemy{bossenemy}
	,m_player{player}
	,m_parent{parent}
	,m_rushDirection{}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossRushAttackRush::~BossRushAttackRush()
{
	// do nothing.
}

void BossRushAttackRush::Initialize()
{



}

BossRushAttackRush::ActionState BossRushAttackRush::Update(const float& elapsedTime)
{


	return ActionState::RUNNING;
}





void BossRushAttackRush::Enter()
{



}

void BossRushAttackRush::Exit()
{



}
