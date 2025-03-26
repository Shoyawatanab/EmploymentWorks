/*
	@file	BossBeamAttackPreliminaryAction.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossBeamAttackPreliminaryAction.h"
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

using namespace DirectX;
using namespace DirectX::SimpleMath;




/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
BossBeamAttackPreliminaryAction::BossBeamAttackPreliminaryAction(CommonResources* resources
	, BossEnemy* bossEnemy
	, Beam* beam
	, BossBeamAttackAction* beamAttack)
	:
	m_commonResources{resources}
	,m_time{}
	, m_bossEnemy{ bossEnemy }
	, m_beam{ beam }
	,m_beamAttack{beamAttack}
{
}

/// <summary>
/// デストラクタ
/// </summary>
BossBeamAttackPreliminaryAction::~BossBeamAttackPreliminaryAction()
{
	// do nothing.
}

void BossBeamAttackPreliminaryAction::Initialize()
{
}

IBehaviorNode::State BossBeamAttackPreliminaryAction::Update(const float& elapsedTime)
{

	if (m_time >= Params::BOSSENEMY_BEAM_BALL_PRELIMINARY_ACTION_TIME)
	{
		m_beamAttack->ChangeState(m_beamAttack->GetBossBeamAttackCharge());

	}



	m_time += elapsedTime;
	return IBehaviorNode::State::Runngin;

}


void BossBeamAttackPreliminaryAction::Enter()
{

	m_time = 0.0f;

	m_bossEnemy->ChangeAnimation("BeamAttack");

}

void BossBeamAttackPreliminaryAction::Exit()
{



}
