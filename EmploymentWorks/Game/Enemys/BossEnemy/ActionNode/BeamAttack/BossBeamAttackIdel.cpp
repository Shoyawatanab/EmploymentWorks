/*
	@file	BossBeamAttackIdel.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossBeamAttackIdel.h"
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
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"
#include "Game/Enemys/BossEnemy/Beam/BeamChargeEffect.h"
#include "Game/Enemys/BossEnemy/Beam/BeamRays.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;




/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
BossBeamAttackIdel::BossBeamAttackIdel(CommonResources* resources
	, BossEnemy* bossenemy
	, Beam* beam
	, BossBeamAttackAction* beamAttack)
	:
	m_commonResources{resources}
	, m_bossEnemy{ bossenemy }
	, m_beam{ beam }
	,m_beamAttack{beamAttack}
{

}

/// <summary>
/// デストラクタ
/// </summary>
BossBeamAttackIdel::~BossBeamAttackIdel()
{
	// do nothing.
}

void BossBeamAttackIdel::Initialize()
{
}

BossBeamAttackIdel::ActionState BossBeamAttackIdel::Update(const float& elapsedTime)
{

	m_beam->Update(elapsedTime);

	m_beamAttack->ChangeState(m_beamAttack->GetBossBeamAttackPreliminaryAction());

	return ActionState::Running;

}


void BossBeamAttackIdel::Enter()
{

	m_beam->GetBeamEnergyBall()->SetPosition(BeamEnergyBall::INITALPOSITION);
	m_beam->SetPosition(BeamEnergyBall::INITALPOSITION);

	m_beam->GetBeamEnergyBall()->SetIsEntityActive(false);
	m_beam->GetBeamRays()->SetIsEntityActive(false);

}

void BossBeamAttackIdel::Exit()
{
}





