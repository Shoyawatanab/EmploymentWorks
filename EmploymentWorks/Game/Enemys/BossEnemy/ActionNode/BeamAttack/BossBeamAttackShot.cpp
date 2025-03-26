/*
	@file	BossBeamAttackShot.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossBeamAttackShot.h"
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
#include "Game/Player/Player.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;




/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
BossBeamAttackShot::BossBeamAttackShot(CommonResources* resources
	, BossEnemy* bossEnemy
	, Beam* beam
	, BossBeamAttackAction* beamAttack
	, Player* player)
	:
	m_commonResources{resources}
	, m_bossEnemy{ bossEnemy }
	, m_beam{ beam }
	,m_beamAttack{beamAttack}
	,m_player{player}
{

}

/// <summary>
/// デストラクタ
/// </summary>
BossBeamAttackShot::~BossBeamAttackShot()
{
	// do nothing.
}

void BossBeamAttackShot::Initialize()
{
}

IBehaviorNode::State BossBeamAttackShot::Update(const float& elapsedTime)
{

	Vector3 position = m_beam->GetBeamEnergyBall()->GetLocalPosition();

	Vector3 moveDirection = Vector3::UnitZ;

	moveDirection *= elapsedTime * Params::BOSSENEMY_BEAM_BALL_MOVE_SPPED;

	position += moveDirection;

	m_beam->GetBeamEnergyBall()->SetLocalPosition(position);

	//ビーム光線の大きさの取得
	Vector3 scale = m_beam->GetBeamRays()->GetLocalScale();

	//ビームの距離を求める
	float distance = Vector3::Distance(m_beam->GetPosition(), m_beam->GetBeamEnergyBall()->GetPosition());

	//モデルのサイズのｚが0.5だからそのままでも大丈夫
	//距離をサイズに
	scale.z = distance;

	//ビーム光線の大きさを
	m_beam->GetBeamRays()->SetLocalScale(scale);

	return IBehaviorNode::State::Runngin;

}


void BossBeamAttackShot::Enter()
{

	m_beam->GetBeamRays()->SetLocalScale(Params::BOSSENEMY_BEAM_RAYS_MAX_SCALE);

	Vector3 s = m_beam->GetScale();
	//敵の現在の座標の取得
	Vector3 startPosition = m_beam->GetPosition();
	//プレイヤの現在の座標の取得
	Vector3 endPosition = m_player->GetPosition() + Vector3(0,1,0);
	//敵からプレイヤの方向ベクトルの計算
	Vector3 toPlayer = endPosition - startPosition;
	//yawの計算　（左右回転）
	//xz平面で敵からプレイヤの方向を求める
	float yaw = atan2(toPlayer.x, toPlayer.z);
	//pitchの計算（上下回転）
	//敵からプレイヤのウ違勅方向を求める
	float pitch = atan2(toPlayer.y, sqrt(toPlayer.x * toPlayer.x + toPlayer.z * toPlayer.z));
	//yaw pitchから回転を計算 pitchは反転させる
	m_beam->SetRotation(Quaternion::CreateFromYawPitchRoll(yaw, -pitch, 0.0f));

	m_beam->GetBeamRays()->SetIsEntityActive(true);


}

void BossBeamAttackShot::Exit()
{
}

