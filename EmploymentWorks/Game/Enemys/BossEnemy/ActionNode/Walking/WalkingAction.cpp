/*
	@file	WalkingAction.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "WalkingAction.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Params.h"
#include "Game/Observer/Messenger.h"

#include "WalkingAction.h"
#include "Game/Entities/CharacterEntity.h"




/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="own">所有者</param>
/// <param name="target">ターゲット</param>
WalkingAction::WalkingAction(CommonResources* resources
	, CharacterEntity* own
	, CharacterEntity* target)
	:
	m_commonResources{resources}
	,m_own{own}
	,m_target{target}
	,m_time{}
{



}

/// <summary>
/// デストラクタ
/// </summary>
WalkingAction::~WalkingAction()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
void WalkingAction::Initialize()
{

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
WalkingAction:: ActionState WalkingAction::Update(const float& elapsedTime)
{
	using namespace DirectX::SimpleMath;


//回転
	//向きたい方向
	Vector3 direction = m_target->GetPosition() - m_own->GetPosition();
	direction.Normalize();
	//今の敵の前方向
	Vector3 forward = Vector3::Transform(Vector3::Backward, m_own->GetRotation());
	//forward.Normalize();
	//回転軸の作成
	Vector3 moveAxis = forward.Cross(direction);

	if (moveAxis.y >= 0.0f)
	{
		//正なら上方向
		moveAxis = Vector3::Up;
	}
	else
	{
		//負なら下方向
		moveAxis = Vector3::Down;
	}

	//角度を求める
	float moveAngle = forward.Dot(direction);


	//ラジアン値に変換
	moveAngle = acosf(moveAngle);

	//角度と速度の比較で小さいほうを取得
	moveAngle = std::min(moveAngle, Params::BOSSENEMY_ROTATION_SPEED * elapsedTime);

	//敵の回転の取得
	Quaternion Rotate = m_own->GetRotation();
	//Y軸に対して回転をかける
	Rotate *= Quaternion::CreateFromAxisAngle(moveAxis, moveAngle);
	m_own->SetRotation(Rotate);


//移動
	//プレイヤの座標の取得
	Vector3 targetPosition = m_target->GetPosition();

	Vector3 ownPosition = m_own->GetPosition();

	//方向を求める
	direction = targetPosition - ownPosition;
	//正規化
	direction.Normalize();

	direction *= Params::BOSSENEMY_MOVE_SPEED * elapsedTime;

	m_own->SetPosition(ownPosition + direction);

	//アニメーションの時間に合わせる
	if (m_time >= WALK_TIME)
	{
		return ActionState::END;
	}

	m_time += elapsedTime;

	return ActionState::RUNNING;

}


/// <summary>
/// 状態に入った時
/// </summary>
void WalkingAction::Enter()
{

	m_own->ChangeAnimation("Move");

	m_time = 0;
}

/// <summary>
/// 状態を抜けた時
/// </summary>
void WalkingAction::Exit()
{
}
