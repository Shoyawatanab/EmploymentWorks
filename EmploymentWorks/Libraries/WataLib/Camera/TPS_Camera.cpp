/*
	@file	TPS_Camera.cpp
	@brief	TPSカメラクラス
*/
#include "pch.h"
#include "TPS_Camera.h"
#include "Game/Screen.h"
#include "Game/Player/Player.h"
#include "Libraries/WataLib/Mouse.h"
#include "Game/Observer/Messenger.h"
#include <cassert>
#include <random>


const POINT MOUSESENSITIVITY = { static_cast<LONG> (0.001f),static_cast<LONG> (0.001f) };      // マウスの感度
const int MAXANGLEY = 100;

const float EXPANSIOOSPEED = 0.7f;   //拡大時のスピード

//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
WataLib::TPS_Camera::TPS_Camera()
	:
	m_view{},
	m_projection{},
	m_eye{},
	m_target{},
	m_up{ DirectX::SimpleMath::Vector3::UnitY },
	m_player{},
	m_angle{},
	m_mouseSensitivity{ 0.001f,0.001f },
	m_lerpTime{},
	m_moveEye{},
	m_zoomState{}
	,m_shakePosition{}
	,m_shaleTime{}
	,m_shakePower{}
{
	m_mouse = std::make_unique<WataLib::Mouse>();

}

WataLib::TPS_Camera::~TPS_Camera()
{


}


void WataLib::TPS_Camera::Initialize(CommonResources* resources)
{
	assert(resources);
	m_mouse->Initialize();
	m_angle = {0,0};
	m_zoomState = ZoomState::None;

	m_target = m_player->GetPosition() + Vector3(0, 1, 0);

	CalculateEyePosition();
	CalculateViewMatrix();
	CalculateProjectionMatrix();


	//イベントにObserverとして登録

	Messenger::GetInstance()->Rigister(GameMessageType::BoomerangGetReady, this);
	Messenger::GetInstance()->Rigister(GameMessageType::BoomerangGetReadyEnd, this);
	Messenger::GetInstance()->Rigister(GameMessageType::CameraShake, this);

}

//-------------------------------------------------------------------
// 更新する
//-------------------------------------------------------------------
void WataLib::TPS_Camera::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();


	m_mouse->Update();

	// targetの位置を更新する
	m_target = m_player->GetPosition() + Vector3(0,1,0);

	m_angle.x -= static_cast<LONG>( m_mouse->GetDiffX());
	m_angle.y -= static_cast<LONG>( m_mouse->GetDiffY());

	//下の制限
	if (m_angle.y > 2100)
	{
		m_angle.y = 2100;
	}
	//上の制限
	if (m_angle.y < -950)
	{
		m_angle.y = -950;

	}


	Vector3 direction = Vector3(0.2, 0, -1);
	//初期化
	m_moveEye = Vector3::Zero;

	switch (m_zoomState)
	{
		case WataLib::TPS_Camera::ZoomState::None:
			break;
		case WataLib::TPS_Camera::ZoomState::ZoomIn:
			//向いている方向
			if (m_lerpTime < 1)
			{
				m_lerpTime += 0.1f * EXPANSIOOSPEED;
			}
			m_moveEye = Vector3::Lerp(Vector3::Zero, direction, m_lerpTime);
			break;
		case WataLib::TPS_Camera::ZoomState::ZoomOut:
			//向いている方向
			if (m_lerpTime > 0)
			{
				m_lerpTime -= 0.1f * EXPANSIOOSPEED;
				m_moveEye = Vector3::Lerp(Vector3::Zero, direction, m_lerpTime);
			}
			else
			{
				m_lerpTime = 0;
				m_moveEye = Vector3::Zero;
				m_zoomState = ZoomState::None;
			}
			break;
		default:
			break;
	}


	Shake(elapsedTime);

	// カメラ座標を計算する
	CalculateEyePosition();
	// ビュー行列を更新する
	CalculateViewMatrix();

	//正面ベクトルを求める



}

void WataLib::TPS_Camera::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	assert(&view);
	assert(&projection);
}

//-------------------------------------------------------------------
// ビュー行列を計算する
//-------------------------------------------------------------------
void WataLib::TPS_Camera::CalculateViewMatrix()
{
	using namespace DirectX::SimpleMath;


	m_view = Matrix::CreateLookAt(m_eye + m_shakePosition, m_target + m_shakePosition, m_up);
}

//-------------------------------------------------------------------
// プロジェクション行列を計算する
//-------------------------------------------------------------------
void WataLib::TPS_Camera::CalculateProjectionMatrix()
{
	using namespace DirectX::SimpleMath;


	// ウィンドウサイズ
	const float width = static_cast<float>(Screen::WIDTH);
	const float height = static_cast<float>(Screen::HEIGHT);
	
	// 画面縦横比
	const float aspectRatio = width / height;

	m_projection = Matrix::CreatePerspectiveFieldOfView(
		FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);
}

//-------------------------------------------------------------------
// カメラ座標を計算する
//-------------------------------------------------------------------
void WataLib::TPS_Camera::CalculateEyePosition()
{

	using namespace DirectX::SimpleMath;


	//プレイヤの回転に使用
	Vector3 angleX = Vector3(0, m_angle.x * m_mouseSensitivity.x, 0);
	m_rotationX = Quaternion::CreateFromYawPitchRoll(angleX);

	//マウスの差分から角度の作成
	Vector3 angle =  Vector3(m_angle.y * m_mouseSensitivity.y, m_angle.x * m_mouseSensitivity.x, 0);

	Vector3 angle2 = Vector3(m_angle.y * m_mouseSensitivity.y, 0, 0);

	//カウスの移動量から回転を生成
	Quaternion Rotation = Quaternion::CreateFromYawPitchRoll(angle);
	//float a = Rotation.x;
	// 既定の進行方向ベクトル
	Vector3 forward = Vector3::Forward;

	// カメラがターゲットからどれくらい離れているか
	forward.y = CAMERA_HIGHT;
	forward.z = CAMERA_DISTANCE;




	// ターゲットの向いている方向に追従する
	forward =   Vector3::Transform(forward, Rotation);
	m_moveEye = Vector3::Transform(m_moveEye, Rotation);

	m_moveEye += forward;

	m_moveEye += m_target;

	// カメラ座標を計算する
	m_eye = m_moveEye;


	//正面ベクトルを求める
	m_forward = (m_target - m_eye);
	m_forward.Normalize();

}

void WataLib::TPS_Camera::AddPointer(Player* Player)
{

	m_player = Player;

}



void WataLib::TPS_Camera::Enter()
{

	m_angle = { 400,800 };

}


void WataLib::TPS_Camera::Exit()
{

}

void WataLib::TPS_Camera::Notify(const Telegram<GameMessageType>& telegram)
{
	

	switch (telegram.messageType)
	{
		case GameMessageType::BoomerangGetReady:
			m_zoomState = ZoomState::ZoomIn;
			break;
		case GameMessageType::BoomerangGetReadyEnd:
			m_zoomState = ZoomState::ZoomOut;
			break;
		case GameMessageType::CameraShake:
			
			m_shaleTime = SHAKETIME;
			m_isShake = true;

			m_shakePower = *static_cast<float*>(telegram.extraInfo);

			break;

		default:
			break;
	}

}

/// <summary>
/// 画面の揺れ
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void WataLib::TPS_Camera::Shake(const float& elapsedTime)
{

	if (!m_isShake)
	{
		return;
	}


	m_shaleTime -= elapsedTime;


	if (m_shaleTime <= 0.0f)
	{
		m_isShake = false;
		m_shakePosition = Vector3::Zero;
		return;
	}

	float power = (m_shaleTime / SHAKETIME) * m_shakePower;

	//	完全なランダムをハードウェア的に生成するためのクラスの変数
	std::random_device seed;
	//	上記の完全なランダムは動作が遅いため、seed値の決定のみに使用する
	//	※「default_random_engine」はusingで「mt19937」となっている
	std::default_random_engine engine(seed());
	//	生成して欲しいランダムの範囲をDistributionに任せる。今回は0～2PI
	std::uniform_real_distribution<> dist(-power, power);

	float x = dist(engine);
	float y = dist(engine);
	float z = dist(engine);
	
	m_shakePosition = Vector3(x, y, z);



}




