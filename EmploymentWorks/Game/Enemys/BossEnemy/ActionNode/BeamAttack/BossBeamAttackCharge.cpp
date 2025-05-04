/*
	@file	BossBeamAttackCharge.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossBeamAttackCharge.h"
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
BossBeamAttackCharge::BossBeamAttackCharge(CommonResources* resources
	, BossEnemy* bossenemy
	, Beam* beam
	, BossBeamAttackAction* beamAttack)
	:
	m_commonResources{resources}
	,m_bossEnemy{bossenemy}
	,m_beam{beam}
	,m_beamAttack{beamAttack}
	,m_particleCreateTime{}
	,m_time{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
BossBeamAttackCharge::~BossBeamAttackCharge()
{
	// do nothing.
}

void BossBeamAttackCharge::Initialize()
{



}

BossBeamAttackCharge::ActionState BossBeamAttackCharge::Update(const float& elapsedTime)
{

	Vector3 beamPosition = Params::BOSSENEMY_BEAM_SHOT_POSITION;

	beamPosition = Vector3::Transform(beamPosition, m_bossEnemy->GetRotation());

	m_beam->SetPosition(beamPosition + m_bossEnemy->GetPosition());


	m_beam->GetBeamEnergyBall()->Update(elapsedTime);

	//進行割合を求める
	float t = m_time / Params::BOSSENEMY_BEAM_BALL_ACCUMULATIONTIME;

	t = std::min(t, 1.0f);

	//サイズの補間
	Vector3 scale = Vector3::Lerp(Vector3::Zero, Params::BOSSENEMY_BEAM_BALL_MAX_SCALE, t);

	m_beam->GetBeamEnergyBall()->SetLocalScale(scale);

	std::vector<std::unique_ptr<BeamChargeEffect>>& effect = m_beam->GetBeamChargeEffect();

	for (auto& eff : effect)
	{
		eff->Update(elapsedTime);

	}

	if (m_particleCreateTime >= Params::BOSSENEMY_BEAM_CHARGE_EFFECT_CREATE_TIME)
	{
		m_beam->CreateParticle();
		m_particleCreateTime = 0;
	}


	if (m_time > Params::BOSSENEMY_BEAM_BALL_ACCUMULATIONTIME)
	{
		return ActionState::End;

	}

	m_time += elapsedTime;
	m_particleCreateTime += elapsedTime;

	return ActionState::Running;

}


void BossBeamAttackCharge::Enter()
{
	m_time = 0;

	m_particleCreateTime = 0;

	//ビームの座標の設定

	Vector3 beamPosition = Params::BOSSENEMY_BEAM_SHOT_POSITION;

	beamPosition = Vector3::Transform(beamPosition, m_bossEnemy->GetRotation());

	m_beam->SetPosition(beamPosition + m_bossEnemy->GetPosition());

	m_beam->CreateParticle();



	m_beam->GetBeamEnergyBall()->SetLocalPosition(Vector3::Zero);
	m_beam->GetBeamRays()->SetLocalPosition(Vector3::Zero);

	m_beam->GetBeamEnergyBall()->SetIsEntityActive(true);



}

void BossBeamAttackCharge::Exit()
{
}

