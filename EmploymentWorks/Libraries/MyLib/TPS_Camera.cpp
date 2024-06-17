/*
	@file	TPS_Camera.cpp
	@brief	TPSカメラクラス
*/
#include "pch.h"
#include "TPS_Camera.h"
#include "Game/Screen.h"
#include "Game/Object/Player.h"

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
	m_player{player}
{
	CalculateEyePosition(DirectX::SimpleMath::Quaternion::Identity);
	CalculateViewMatrix();
	CalculateProjectionMatrix();
}

//-------------------------------------------------------------------
// 更新する
//-------------------------------------------------------------------
void mylib::TPS_Camera::Update(float elapsedTime)
{
	// targetの位置を更新する
	m_target = m_player->GetPosition();

	// カメラ座標を計算する
	CalculateEyePosition(m_player->GetRotate());
	// ビュー行列を更新する
	CalculateViewMatrix();
}

//-------------------------------------------------------------------
// ビュー行列を計算する
//-------------------------------------------------------------------
void mylib::TPS_Camera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
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
void mylib::TPS_Camera::CalculateEyePosition(const DirectX::SimpleMath::Quaternion& rotate)
{
	// 既定の進行方向ベクトル
	DirectX::SimpleMath::Vector3 forward = DirectX::SimpleMath::Vector3::Forward;

	// カメラがターゲットからどれくらい離れているか
	forward.y = CAMERA_HIGHT;
	forward.z = CAMERA_DISTANCE;

	// ターゲットの向いている方向に追従する
	forward = DirectX::SimpleMath::Vector3::Transform(forward, rotate);

	// カメラ座標を計算する
	m_eye = m_target + forward;
}
