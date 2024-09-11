/*
	@file	TPS_Camera.cpp
	@brief	TPSカメラクラス
*/
#include "pch.h"
#include "TPS_Camera.h"
#include "Game/Screen.h"
#include "Game/Object/Player/Player.h"
#include "Libraries/MyLib/Mouse.h"

const POINT MOUSESENSITIVITY = { 0.001f,0.001f };      // マウスの感度
const int MAXANGLEY = 100;

const float EXPANSIOOSPEED = 0.7f;   //拡大時のスピード

//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
mylib::TPS_Camera::TPS_Camera(Player* player)
	:
	m_view{},
	m_projection{},
	m_eye{},
	m_target{},
	m_up{ DirectX::SimpleMath::Vector3::UnitY },
	m_player{player},
	m_angle{},
	m_mouseSensitivity{ 0.001f,0.001f },
	m_lerpTime{},
	m_moveEye{},
	m_zoomState{ ZoomState::None }
{
	m_mouse = new mylib::Mouse;
	m_mouse->Initialize();

}


void mylib::TPS_Camera::Initialize()
{

	m_mouse->Initialize();
	m_angle = {0,0};

	m_target = m_player->GetPosition();

	CalculateEyePosition();
	CalculateViewMatrix();
	CalculateProjectionMatrix();

}

//-------------------------------------------------------------------
// 更新する
//-------------------------------------------------------------------
void mylib::TPS_Camera::Update(const float& elapsedTime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();


	m_mouse->Update(elapsedTime);

	// targetの位置を更新する
	m_target = m_player->GetPosition();

	m_angle.x -= m_mouse->GetDiffX();
	m_angle.y -= m_mouse->GetDiffY();

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
	if (key.IsKeyDown(Keyboard::Keyboard::Space))
	{
		m_zoomState = ZoomState::ZoomIn;
	}

	if (key.IsKeyUp(Keyboard::Keyboard::Space) && m_zoomState == ZoomState::ZoomIn)
	{
		m_zoomState = ZoomState::ZoomOut;
	}

	Vector3 direction = Vector3::Zero;
	switch (m_zoomState)
	{
		case mylib::TPS_Camera::ZoomState::None:
			break;
		case mylib::TPS_Camera::ZoomState::ZoomIn:
			//向いている方向
			direction = m_target - m_eye;
			direction.Normalize();
			direction *= 4;
			if (m_lerpTime < 1)
			{
				m_lerpTime += 0.1f * EXPANSIOOSPEED;
			}
			m_moveEye = Vector3::Lerp(Vector3::Zero, direction, m_lerpTime);
			break;
		case mylib::TPS_Camera::ZoomState::ZoomOut:
			//向いている方向
			direction = m_target - m_eye;
			direction.Normalize();
			direction *= 2;
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
}

//-------------------------------------------------------------------
// ビュー行列を計算する
//-------------------------------------------------------------------
void mylib::TPS_Camera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye + m_moveEye, m_target, m_up);
}

//-------------------------------------------------------------------
// プロジェクション行列を計算する
//-------------------------------------------------------------------
void mylib::TPS_Camera::CalculateProjectionMatrix()
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
void mylib::TPS_Camera::CalculateEyePosition()
{
	DirectX::SimpleMath::Vector3 angleX = DirectX::SimpleMath::Vector3(0, m_angle.x * m_mouseSensitivity.x, 0);
	m_rotationX = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(angleX);

	//マウスの差分から角度の作成
	DirectX::SimpleMath::Vector3 angle = DirectX::SimpleMath::Vector3(m_angle.y * m_mouseSensitivity.y, m_angle.x * m_mouseSensitivity.x, 0);
	DirectX::SimpleMath::Quaternion Rotation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(angle);
	//float a = Rotation.x;
	// 既定の進行方向ベクトル
	DirectX::SimpleMath::Vector3 forward = DirectX::SimpleMath::Vector3::Forward;

	// カメラがターゲットからどれくらい離れているか
	forward.y = CAMERA_HIGHT;
	forward.z = CAMERA_DISTANCE;

	m_player->SetCameraRotate(m_rotationX);


	// ターゲットの向いている方向に追従する
	forward = DirectX::SimpleMath::Vector3::Transform(forward, Rotation);
	// カメラ座標を計算する
	m_eye = m_target + forward;
}


void mylib::TPS_Camera::Enter()
{

	m_angle = { 400,800 };

}


void mylib::TPS_Camera::Exit()
{

}



