/*
	@file	RisingPillarPreliminaryAction.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "RisingPillarPreliminaryAction.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Params.h"
#include "Game/Enemys/BossEnemy/BossEnemy.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "Game/Enemys/BossEnemy/ActionNode/BeamAttack/BossBeamAttackAction.h"
#include "Game/Enemys/BossEnemy/ActionNode/RisingPillar/RisingPillarvAction.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;




/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
RisingPillarPreliminaryAction::RisingPillarPreliminaryAction(
	RisingPillarvAction* risingPillarvAction,
	BossEnemy* bossEnemy
	)
	:
	m_time{}
	, m_bossEnemy{ bossEnemy }
	,m_risingPillarvAction{risingPillarvAction}
{
}

/// <summary>
/// デストラクタ
/// </summary>
RisingPillarPreliminaryAction::~RisingPillarPreliminaryAction()
{
	// do nothing.
}

void RisingPillarPreliminaryAction::Initialize(CommonResources* resources)
{
	m_commonResources = resources;
}

IBehaviorNode::State RisingPillarPreliminaryAction::Update(const float& elapsedTime)
{
	
	if (m_time >= 2.0f)
	{
		m_risingPillarvAction->ChangeState(m_risingPillarvAction->GetPillarRise());

	}


	m_time += elapsedTime;
	return IBehaviorNode::State::Runngin;

}


void RisingPillarPreliminaryAction::Enter()
{

	m_time = 0.0f;

	m_bossEnemy->ChangeAnimation("BeamAttack");

}

void RisingPillarPreliminaryAction::Exit()
{



}
