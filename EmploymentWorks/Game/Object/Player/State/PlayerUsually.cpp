
#include "pch.h"
#include "Game/Object/Player/State/PlayerUsually.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/Player.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"

const float MOVE_SPEED = 5.0f;                                        //動く時のスピード
const DirectX::SimpleMath::Vector3 INITIAL_DIRECTION(0.0f, 0.0f, -1.0f); //初期の向いている方向

void PlayerUsually::ResetGravity()
{

	//m_graivty = 0;

}

// コンストラクタ
PlayerUsually::PlayerUsually()
	:
	m_commonResources{},
	m_player{}
	,m_graivty{}
{



}

// デストラクタ
PlayerUsually::~PlayerUsually()
{

}

// 初期化する
void PlayerUsually::Initialize()
{
	m_graivty = 0.5f;
}


// 更新する
void PlayerUsually::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	//マウスの取得


	// キーボードステートを取得する
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();
	// キーボードステートトラッカーを取得する
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

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

	moveDirection = Vector3::Transform(moveDirection, m_player->GetCameraRotate());
	
	Rotate(elapsedTime, moveDirection);

	Move(elapsedTime,   moveDirection);
	

	// スペースキーが押されたら
	if (kbTracker->released.Space)
	{
		//状態をジャンプに変更
		m_player->ChangeState(m_player->GetPlayerJump());

	}

	DirectX::SimpleMath::Vector3 velocity = m_player->GetVelocity();
	velocity.y -= m_graivty * elapsedTime;

	//座標の更新
	DirectX::SimpleMath::Vector3 Pos = m_player->GetPosition();
	Pos += velocity;

	m_player->SetPosition(Pos);
	m_player->SetVelocity(velocity);

}


void PlayerUsually::Enter()
{

}

void PlayerUsually::Exit()
{

}

void PlayerUsually::RegistrationInformation(CommonResources* resoure,Player* player)
{
	m_commonResources = resoure;
	m_player = player;

}

void PlayerUsually::Move(float elapsedTime,  DirectX::SimpleMath::Vector3 moveDirection)
{

	using namespace DirectX::SimpleMath;

	if (moveDirection == Vector3::Zero)
	{
		return;
	}
	
	moveDirection;
	DirectX::SimpleMath::Vector3 Pos = m_player->GetPosition();

	Pos += moveDirection *= MOVE_SPEED * elapsedTime;

	m_player->SetPosition(Pos);
}


void PlayerUsually::Rotate(float elapsedTime, DirectX::SimpleMath::Vector3 moveDirection)
{

	UNREFERENCED_PARAMETER(elapsedTime);
	UNREFERENCED_PARAMETER(moveDirection);
	using namespace DirectX::SimpleMath;

	DirectX::SimpleMath::Vector3 Direction = m_player->GetPlayerForWard();
	Quaternion rotation = m_player->GetCameraRotate();


	Direction = Vector3::Transform(INITIAL_DIRECTION, rotation);

	Direction.Normalize();

	m_player->SetPlayerForWard(Direction);

	//rotation;
	//初期値とカメラの回転をもとにする
	m_player->SetAngle(m_player->GetInitialAngle() *  rotation);


	return;


	////ブーメランを構えたら
	//if (m_player->GetUsingBoomerang()->GetBoomerangState() == m_player->GetUsingBoomerang()->GetBoomerangGetReady())
	//{
	//	//カメラの向いている方向にプレイヤの正面を合わせる

	//	m_player->SetRotate(m_player->GetCameraRotate());
	//	m_player->SetPlayerForWard(Vector3::Transform(INITIAL_DIRECTION, m_player->GetRotate())) ;

	//	m_player->GetPlayerForWard().Normalize();


	//}
	//else
	//{
	//	////構えていないとき
	//	DirectX::SimpleMath::Vector3 Direction = m_player->GetPlayerForWard();
	//	Quaternion rotation = m_player->GetCameraRotate();



	//	m_player->SetRotate(rotation);

	//	Direction = Vector3::Transform(INITIAL_DIRECTION, rotation);

	//	Direction.Normalize();

	//	m_player->SetPlayerForWard(Direction);


	//	if (moveDirection == Vector3::Zero)
	//	{
	//		return;
	//	}
	//	moveDirection.Normalize();

	//	DirectX::SimpleMath::Vector3 Direction = m_player->GetPlayerForWard();

	//	//現在の向きと動く方向から軸を作る
	//	Vector3 axis = moveDirection.Cross(Direction);

	//	if (axis == Vector3::Zero)
	//	{
	//		axis = Vector3::UnitY;
	//	}

	//	//
	//	axis *= -1;

	//	float  angle = Vector3::Distance(moveDirection, Direction);
	//	angle *= elapsedTime * 10.0f;
	//	Quaternion rotation = m_player->GetRotate();
	//	rotation *= Quaternion::CreateFromAxisAngle(axis, angle);

	//	m_player->SetRotate(rotation);




	//}


}
