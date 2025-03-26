/*
	@file	BossBeamAttackEnd.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossBeamAttackEnd.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Game/MathUtil.h"

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
BossBeamAttackEnd::BossBeamAttackEnd(CommonResources* resources
	, BossEnemy* bossenemy
	, Beam* beam
	, BossBeamAttackAction* beamAttack)
	:
	m_commonResources{resources}
	, m_bossEnemy{ bossenemy }
	, m_beam{ beam }
	,m_beamAttack{beamAttack}
	,m_time{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
BossBeamAttackEnd::~BossBeamAttackEnd()
{
	// do nothing.
}

void BossBeamAttackEnd::Initialize()
{
}

IBehaviorNode::State BossBeamAttackEnd::Update(const float& elapsedTime)
{

	float t = m_time / Params::BOSSENEMY_BEAM_SHRINK_TIME;

	Vector3 scale = m_beam->GetBeamRays()->GetLocalScale();

	scale.x = MathUtil::Lerp(Params::BOSSENEMY_BEAM_RAYS_MAX_SCALE.x, 0.0f, t);
	scale.y = MathUtil::Lerp(Params::BOSSENEMY_BEAM_RAYS_MAX_SCALE.y, 0.0f, t);

	m_beam->GetBeamRays()->SetLocalScale(scale);

	

	scale = m_beam->GetBeamEnergyBall()->GetLocalScale();

	scale = Vector3::Lerp(Params::BOSSENEMY_BEAM_BALL_MAX_SCALE, Vector3::Zero, t);

	scale.x = std::max(scale.x, 0.0f);
	scale.y = std::max(scale.y, 0.0f);
	scale.z = std::max(scale.z, 0.0f);


	m_beam->GetBeamEnergyBall()->SetLocalScale(scale);


	m_time += elapsedTime;
	m_time = std::min(m_time, Params::BOSSENEMY_BEAM_SHRINK_TIME);

	if (m_time == Params::BOSSENEMY_BEAM_SHRINK_TIME)
	{
		m_beamAttack->ChangeState(m_beamAttack->GetBossBeamAttackIdel());
		return IBehaviorNode::State::Success;
	}


	m_time += elapsedTime;
	return IBehaviorNode::State::Runngin;

}



void BossBeamAttackEnd::Enter()
{
	m_bossEnemy->ChangeAnimation("BeamAttackEnd");
	m_time = 0;
}

void BossBeamAttackEnd::Exit()
{
}





