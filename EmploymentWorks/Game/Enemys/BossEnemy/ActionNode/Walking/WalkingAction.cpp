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

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
WalkingAction::WalkingAction(CommonResources* resources
	, CharacterEntity* own
	, CharacterEntity* target)
	:
	m_commonResources{resources}
	,m_own{own}
	,m_target{target}
{



}

/// <summary>
/// デストラクタ
/// </summary>
WalkingAction::~WalkingAction()
{
	// do nothing.
}

void WalkingAction::Initialize()
{

}

WalkingAction:: ActionState WalkingAction::Update(const float& elapsedTime)
{

//回転
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
	if (m_time >= 4.0f)
	{
		return ActionState::End;
	}

	m_time += elapsedTime;

	return ActionState::Running;

}



void WalkingAction::Enter()
{

	m_own->ChangeAnimation("Move");

	m_time = 0;
}

void WalkingAction::Exit()
{
}
