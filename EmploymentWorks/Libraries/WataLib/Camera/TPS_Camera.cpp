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

using namespace DirectX;
using namespace DirectX::SimpleMath;


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
{
	m_mouse = std::make_unique<WataLib::Mouse>();

}

WataLib::TPS_Camera::~TPS_Camera()
{
}


void WataLib::TPS_Camera::Initialize(CommonResources* resources)
{

	m_mouse->Initialize();
	m_angle = {0,0};
	m_zoomState = ZoomState::None;

	m_target = m_player->GetPosition() + Vector3(0, 1, 0);

	CalculateEyePosition();
	CalculateViewMatrix();
	CalculateProjectionMatrix();


	//イベントにObserverとして登録

	Messenger::Attach(EventParams::EventType::BoomerangGetReady, this);
	Messenger::Attach(EventParams::EventType::BoomerangGetReadyEnd, this);

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


	// カメラ座標を計算する
	CalculateEyePosition();
	// ビュー行列を更新する
	CalculateViewMatrix();

	//正面ベクトルを求める



}

void WataLib::TPS_Camera::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
}

//-------------------------------------------------------------------
// ビュー行列を計算する
//-------------------------------------------------------------------
void WataLib::TPS_Camera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

//-------------------------------------------------------------------
// プロジェクション行列を計算する
//-------------------------------------------------------------------
void WataLib::TPS_Camera::CalculateProjectionMatrix()
{
	// ウィンドウサイズ
	const float width = static_cast<float>(Screen::WIDTH);
	const float height = static_cast<float>(Screen::HEIGHT);
	
	// 画面縦横比
	const float aspectRatio = width / height;

	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);
}

//-------------------------------------------------------------------
// カメラ座標を計算する
//-------------------------------------------------------------------
void WataLib::TPS_Camera::CalculateEyePosition()
{
	//プレイヤの回転に使用
	DirectX::SimpleMath::Vector3 angleX = DirectX::SimpleMath::Vector3(0, m_angle.x * m_mouseSensitivity.x, 0);
	m_rotationX = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(angleX);

	//マウスの差分から角度の作成
	DirectX::SimpleMath::Vector3 angle = DirectX::SimpleMath::Vector3(m_angle.y * m_mouseSensitivity.y, m_angle.x * m_mouseSensitivity.x, 0);

	DirectX::SimpleMath::Vector3 angle2 = DirectX::SimpleMath::Vector3(m_angle.y * m_mouseSensitivity.y, 0, 0);

	//カウスの移動量から回転を生成
	DirectX::SimpleMath::Quaternion Rotation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(angle);
	//float a = Rotation.x;
	// 既定の進行方向ベクトル
	DirectX::SimpleMath::Vector3 forward = DirectX::SimpleMath::Vector3::Forward;

	// カメラがターゲットからどれくらい離れているか
	forward.y = CAMERA_HIGHT;
	forward.z = CAMERA_DISTANCE;




	// ターゲットの向いている方向に追従する
	forward = DirectX::SimpleMath::Vector3::Transform(forward, Rotation);
	m_moveEye = DirectX::SimpleMath::Vector3::Transform(m_moveEye, Rotation);

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

void WataLib::TPS_Camera::Notify(EventParams::EventType type, void* datas)
{

	switch (type)
	{
		case EventParams::EventType::BoomerangGetReady:
			m_zoomState = ZoomState::ZoomIn;
			break;
		case EventParams::EventType::BoomerangGetReadyEnd:
			m_zoomState = ZoomState::ZoomOut;
			break;
		default:
			break;
	}

}




