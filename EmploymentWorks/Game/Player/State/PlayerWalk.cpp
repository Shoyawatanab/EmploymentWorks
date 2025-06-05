#include "pch.h"
#include "PlayerWalk.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"


#include "Game/Player/Player2.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Observer/Messenger.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Camera/PayScene/PlaySceneCamera.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerWalk::PlayerWalk(PlayerStateMachine* stateMachine, Player2* player)
	:
	m_stateMahine{stateMachine}
	, m_player{ player }
	,m_rigidbody{}
	,m_moveDirection{}
{

	m_rigidbody=  player->GetComponent<RigidbodyComponent>();

}

/// <summary>
/// デストラクタ
/// </summary>
PlayerWalk::~PlayerWalk()
{
}



/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void PlayerWalk::Update(const float& deltatime)
{
	using namespace DirectX::SimpleMath;

	m_moveDirection = Vector3::Zero;

	//移動
	Move(deltatime);

	//回転
	Rotate(deltatime);




}


/// <summary>
/// 状態に入った時
/// </summary>
void PlayerWalk::Enter()
{

	//減速率の設定
	m_rigidbody->SetDeceleration(Params::GRAUND_FRICTION);


}

/// <summary>
/// 状態を抜けた時
/// </summary>
void PlayerWalk::Exit()
{
}

/// <summary>
/// 移動
/// </summary>
void PlayerWalk::Move(const float& deltatime)
{

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	// キーボードステートを取得する
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();

	Transform* transform = m_player->GetTransform();

	float moveSpeed = Params::PLAYER_MOVE_SPEED * deltatime;


	if (key.IsKeyDown(Keyboard::Keyboard::W))
	{
		m_moveDirection.z--;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::S))
	{
		m_moveDirection.z++;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::A))
	{
		m_moveDirection.x--;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::D))
	{
		m_moveDirection.x++;
	}

	//カメラの横の回転軸から回転の計算
	Quaternion rotationX =Quaternion::CreateFromYawPitchRoll( m_player->GetPlaySceneCamera()->GetRotationY(),0.0f,0.0f);
	//カメラの回転に沿って回転
	m_moveDirection = Vector3::Transform(m_moveDirection, rotationX);

	//移動
	m_rigidbody->AddForce(m_moveDirection * moveSpeed);

}

void PlayerWalk::Rotate(const float& deltatime)
{
	using namespace DirectX::SimpleMath;

	Quaternion rotate = m_player->GetTransform()->GetRotate();
	//正面ベクトルの取得
	Vector3 playerForward = m_player->GetTransform()->GetForwardVector();
	//回転軸を求める
	Vector3 rotationAxis = m_moveDirection.Cross(playerForward);
	//軸がセロなら
	if (rotationAxis == Vector3::Zero)
	{
		return;
	}
	//値が小さい時は正規化
	if (m_moveDirection.LengthSquared() > 0.0001f)
	{
		m_moveDirection.Normalize();
	}	
	//軸の反転
	rotationAxis *= -1;
	//角度を求める
	float angle = Vector3::Distance(m_moveDirection, playerForward);

	angle *= deltatime * Params::PLAYER_ROTATION_SPEED;
	//回転を加算する
	Quaternion rotation = Quaternion::CreateFromAxisAngle(rotationAxis, angle);

	m_player->GetTransform()->SetRotate(m_player->GetTransform()->GetRotate() * rotation);



}



