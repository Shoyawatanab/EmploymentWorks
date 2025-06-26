/*
	@file	BossBeamAttackShot.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossBeamAttackShot.h"
#include "GameBase/Common/Commons.h"


#include "Game/Params.h"
#include "Game/Player/Player.h"




/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="bossEnemy">所有者</param>
/// <param name="beam">ビーム</param>
/// <param name="beamAttack">ビーム攻撃</param>
/// <param name="player">プレイヤ</param>
BossBeamAttackShot::BossBeamAttackShot(Actor* bossEnemy
	, BossEnemyBeam* beam
	, BossBeamAttackActionController* beamAttack
	, Actor* player)
	:
	m_commonResources{}
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


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
BossBeamAttackShot::ActionState BossBeamAttackShot::Update(const float& elapsedTime)
{
	////エネルギー弾の取得
	//Vector3 position = m_beam->GetBeamEnergyBall()->GetLocalPosition();
	////動かす方向
	//Vector3 moveDirection = Vector3::UnitZ;
	////どれだけ動かすか
	//moveDirection *= elapsedTime * Params::BOSSENEMY_BEAM_BALL_MOVE_SPPED;
	////座標を加算
	//position += moveDirection;
	////座標の登録
	//m_beam->GetBeamEnergyBall()->SetLocalPosition(position);

	////ビーム光線の大きさの取得
	//Vector3 scale = m_beam->GetBeamRays()->GetLocalScale();

	////ビームの距離を求める
	//float distance = Vector3::Distance(m_beam->GetPosition(), m_beam->GetBeamEnergyBall()->GetPosition());

	////モデルのサイズのｚが0.5だからそのままでも大丈夫
	////距離をサイズに
	//scale.z = distance;

	////ビーム光線の大きさを
	//m_beam->GetBeamRays()->SetLocalScale(scale);

	return ActionState::RUNNING;

}

/// <summary>
/// 状態に入った時
/// </summary>
void BossBeamAttackShot::Enter()
{

	//m_beam->GetBeamRays()->SetLocalScale(Params::BOSSENEMY_BEAM_RAYS_MAX_SCALE);

	//Vector3 s = m_beam->GetScale();
	////敵の現在の座標の取得
	//Vector3 startPosition = m_beam->GetPosition();
	////プレイヤの現在の座標の取得　少し上を狙うようにする
	//Vector3 endPosition = m_player->GetPosition() + TARGET_OFFSET;
	////敵からプレイヤの方向ベクトルの計算
	//Vector3 toPlayer = endPosition - startPosition;
	////yawの計算　（左右回転）
	////xz平面で敵からプレイヤの方向を求める
	//float yaw = atan2(toPlayer.x, toPlayer.z);
	////pitchの計算（上下回転）
	////敵からプレイヤのウ違勅方向を求める
	//float pitch = atan2(toPlayer.y, sqrt(toPlayer.x * toPlayer.x + toPlayer.z * toPlayer.z));
	////yaw pitchから回転を計算 pitchは反転させる
	//m_beam->SetRotation(Quaternion::CreateFromYawPitchRoll(yaw, -pitch, 0.0f));

	//m_beam->GetBeamRays()->SetIsEntityActive(true);

	//m_beam->GetBeamEnergyBall()->SetIsCollisionActive(true);


}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BossBeamAttackShot::Exit()
{
	//m_beam->GetBeamEnergyBall()->SetIsCollisionActive(false);

}

