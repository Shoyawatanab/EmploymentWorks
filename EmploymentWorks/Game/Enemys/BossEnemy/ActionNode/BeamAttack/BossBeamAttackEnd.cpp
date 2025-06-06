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
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "Game/Enemys/BossEnemy/ActionNode/BeamAttack/BossBeamAttackAction.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"
#include "Game/Enemys/BossEnemy/Beam/BeamChargeEffect.h"
#include "Game/Enemys/BossEnemy/Beam/BeamRays.h"



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="bossenemy">所有者</param>
/// <param name="beam">ビーム</param>
/// <param name="beamAttack">ビーム攻撃</param>
BossBeamAttackEnd::BossBeamAttackEnd(CommonResources* resources
	, CharacterEntity* bossenemy
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

/// <summary>
/// 初期化
/// </summary>
void BossBeamAttackEnd::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
BossBeamAttackEnd::ActionState BossBeamAttackEnd::Update(const float& elapsedTime)
{

	//float t = m_time / Params::BOSSENEMY_BEAM_SHRINK_TIME;

	//Vector3 scale = m_beam->GetBeamRays()->GetLocalScale();

	//scale.x = MathUtil::Lerp(Params::BOSSENEMY_BEAM_RAYS_MAX_SCALE.x, 0.0f, t);
	//scale.y = MathUtil::Lerp(Params::BOSSENEMY_BEAM_RAYS_MAX_SCALE.y, 0.0f, t);

	//m_beam->GetBeamRays()->SetLocalScale(scale);

	//

	//scale = m_beam->GetBeamEnergyBall()->GetLocalScale();

	//scale = Vector3::Lerp(Params::BOSSENEMY_BEAM_BALL_MAX_SCALE, Vector3::Zero, t);

	//scale.x = std::max(scale.x, 0.0f);
	//scale.y = std::max(scale.y, 0.0f);
	//scale.z = std::max(scale.z, 0.0f);


	//m_beam->GetBeamEnergyBall()->SetLocalScale(scale);


	//m_time += elapsedTime;
	//m_time = std::min(m_time, Params::BOSSENEMY_BEAM_SHRINK_TIME);

	//if (m_time == Params::BOSSENEMY_BEAM_SHRINK_TIME)
	//{
	//	return ActionState::END;
	//}


	//m_time += elapsedTime;

	return ActionState::RUNNING;

}


/// <summary>
/// 状態に入った時
/// </summary>
void BossBeamAttackEnd::Enter()
{
	//m_bossEnemy->ChangeAnimation("BeamAttackEnd");
	m_time = 0;
}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BossBeamAttackEnd::Exit()
{
}





