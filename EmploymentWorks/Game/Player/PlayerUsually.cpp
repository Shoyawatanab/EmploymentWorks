#include "pch.h"
#include "PlayerUsually.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Observer/Messenger.h"
#include "Game/Params.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
PlayerUsually::PlayerUsually()
	:
	m_commonResources{}
	,m_palyer{}
	,m_tpsCamera{}
	,m_gravity{}
	,m_isGetReady{false}
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerUsually::~PlayerUsually()
{
}


/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="player">プレイヤ</param>
/// <param name="tpsCamera">TPSカメラ</param>
void PlayerUsually::AddPointer(Player* player, WataLib::TPS_Camera* tpsCamera)
{
	m_palyer = player;

	m_tpsCamera = tpsCamera;
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void PlayerUsually::Initialize(CommonResources* resources)
{
	m_commonResources = resources;


	m_gravity = Params::GRAVITY;

	//イベントにObserverとして登録
	Messenger::GetInstance()->Attach(::MessageType::BoomerangGetReady, this);
	Messenger::GetInstance()->Attach(::MessageType::BoomerangGetReadyEnd, this);
}


/// <summary>
/// 動き
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <param name="moveDirection">動く方向</param>
void PlayerUsually::Move(const float& elapsedTime, DirectX::SimpleMath::Vector3 moveDirection)
{
	//プレイヤ座標の取得
	Vector3 position = m_palyer->GetPosition();
	
	position += moveDirection * elapsedTime * Params::PLAYER_MOVE_SPEED;

	//プレイヤの座標を設定
	m_palyer->SetPosition(position);


}

/// <summary>
/// 回転
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <param name="moveDirection">動く方向</param>
void PlayerUsually::Rotation(const float& elapsedTime, DirectX::SimpleMath::Vector3 moveDirection)
{
	//構えていないとき
	//if (m_palyer->GetPlayerStateMachine()->GetCurrentState() != m_palyer->GetPlayerStateMachine()->GetPlayerAttack())
	if (!m_isGetReady)
	{
		//プレイヤの回転の取得
		Quaternion rotation = m_palyer->GetRotation();
		//プレイヤの正面
		Vector3 playerUsuallyForward = Vector3::Transform(Vector3::Forward, rotation);
		//回転軸を求める
		Vector3 rotationAxis = moveDirection.Cross(playerUsuallyForward);

		//軸が０の時
		if (rotationAxis == Vector3::Zero)
		{
			return;
		}
		//正規化
		rotationAxis.Normalize();
		//軸の反転
		rotationAxis *= -1;
		//角度を求める
		float angle = Vector3::Distance(moveDirection, playerUsuallyForward);

		angle *= elapsedTime * Params::PLAYER_ROTATION_SPEED;
		//回転を加算する
		rotation *= Quaternion::CreateFromAxisAngle(rotationAxis, angle);
		//回転を設定
		m_palyer->SetRotation(rotation);
	}
	//構えているとき
	else
	{

		Quaternion rotation = m_tpsCamera->GetRotationX();


		m_palyer->SetRotation(rotation);

	}
}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">種類</param>
/// <param name="datas">データ</param>
void PlayerUsually::Notify(const Telegram& telegram)
{
	
	//イベントの種類
	switch (telegram.messageType)
	{
		case ::MessageType::BoomerangGetReady:
			//構えている
			m_isGetReady = true;
			break;
		case ::MessageType::BoomerangGetReadyEnd:
			//構えていない
			m_isGetReady = false;
			break;
		default:
			break;
	}
}






/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void PlayerUsually::Update(const float& elapsedTime)
{
	// キーボードステートを取得する
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();



	Vector3 moveDirection = Vector3::Zero;

	if (key.IsKeyDown(Keyboard::Keyboard::W))
	{
		moveDirection.z--;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::S))
	{
		moveDirection.z++;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::A))
	{
		moveDirection.x--;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::D))
	{
		moveDirection.x++;
	}

	//カメラの向いている方向をもとに回転
	moveDirection = Vector3::Transform(moveDirection, m_tpsCamera->GetRotationX());
	moveDirection.Normalize();


	Move(elapsedTime,moveDirection);

	Rotation(elapsedTime, moveDirection);

	//重力
	Vector3 position = m_palyer->GetPosition();

	position.y -= m_gravity * elapsedTime;

	m_palyer->SetPosition(position);

	Vector3 velocity = m_palyer->GetVelocity();

	velocity.y -= m_gravity * elapsedTime;




	//アニメーションを管理
	//動いている
	if (moveDirection != Vector3::Zero)
	{
		//プレイヤアニメーションがIdle状態なら
		if (m_palyer->GetCurrentAnimationType() == "Idle")
		{
			//アニメーションを変更
			m_palyer->ChangeAnimation("Move");
		}
	}
	//動いていない
	else
	{
		//プレイヤアニメーションがIdle状態なら
		if (m_palyer->GetCurrentAnimationType() == "Move")
		{
			//アニメーションを変更
			m_palyer->ChangeAnimation("Idle");
		}

	}

}





