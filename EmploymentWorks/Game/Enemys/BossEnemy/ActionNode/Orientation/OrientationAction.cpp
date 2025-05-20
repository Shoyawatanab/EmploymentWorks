/*
	@file	OrientationAction.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "OrientationAction.h"
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

#include "OrientationAction.h"
#include "Game/Entities/BaseEntity.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="own">所有者</param>
/// <param name="target">ターゲット</param>
OrientationAction::OrientationAction(CommonResources* resources
	, BaseEntity* own
	, BaseEntity* target)
	:
	m_commonResources{resources}
	,m_own{own}
	,m_target{target}
{



}

/// <summary>
/// デストラクタ
/// </summary>
OrientationAction::~OrientationAction()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
void OrientationAction::Initialize()
{

}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
OrientationAction:: ActionState OrientationAction::Update(const float& elapsedTime)
{

	//向きたい方向
	DirectX::SimpleMath::Vector3 direction = m_target->GetPosition() - m_own->GetPosition();
	direction.Normalize();
	//今の敵の前方向
	DirectX::SimpleMath::Vector3 forward = Vector3::Transform(Vector3::Backward, m_own->GetRotation());
	//forward.Normalize();
	//回転軸の作成
	DirectX::SimpleMath::Vector3 moveAxis = forward.Cross(direction);

	if (moveAxis.y >= 0.0f)
	{
		//正なら上方向
		moveAxis = DirectX::SimpleMath::Vector3::Up;
	}
	else
	{
		//負なら下方向
		moveAxis = DirectX::SimpleMath::Vector3::Down;
	}

	//角度を求める
	float moveAngle = forward.Dot(direction);


	//ラジアン値に変換
	moveAngle = acosf(moveAngle);

	//角度と速度の比較で小さいほうを取得
	moveAngle = std::min(moveAngle, Params::BOSSENEMY_ROTATION_SPEED * elapsedTime);

	//敵の回転の取得
	DirectX::SimpleMath::Quaternion Rotate = m_own->GetRotation();
	//Y軸に対して回転をかける
	Rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(moveAxis, moveAngle);
	m_own->SetRotation(Rotate);


	// 敵の今の前方向を更新
	forward = Vector3::Transform(Vector3::Backward, m_own->GetRotation());
	forward.Normalize();

	// プレイヤー方向との差を再計算
	float alignment = forward.Dot(direction);

	// 角度が小さい（向けている）なら追加処理
	const float threshold = cosf(DirectX::XMConvertToRadians(Params::ENEMY_PERMISSIBLE_ANGLE)); // 5度以内ならOKとする

	if (alignment >= threshold)
	{
		return ActionState::END;
	}



	return ActionState::RUNNING;


}


/// <summary>
/// 状態に入った時
/// </summary>
void OrientationAction::Enter()
{


}

/// <summary>
/// 状態を抜けた時
/// </summary>
void OrientationAction::Exit()
{
}
