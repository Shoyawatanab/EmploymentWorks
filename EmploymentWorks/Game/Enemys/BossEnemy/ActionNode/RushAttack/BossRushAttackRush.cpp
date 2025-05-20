/*
	@file	BossRushAttackRush.cpp
	@brief	プレイシーンクラス
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
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
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
/// デストラクタ
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
