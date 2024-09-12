/*
	@file	GameEndCamera.cpp
	@brief	TPSカメラクラス
*/
#include "pch.h"
#include "GameEndCamera.h"
#include "Game/Screen.h"
#include "Libraries/MyLib/Mouse.h"
#include "Game/Object/Enemy/Enemy.h"
#include "Libraries/MyLib/Camera/GameCameraManager.h"

const DirectX::SimpleMath::Vector3 TARGET = DirectX::SimpleMath::Vector3(0, 1, 0); //ステージの中心

const float MAXTIME = 4;



//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
mylib::GameEndCamera::GameEndCamera(GameCameraManager* cameraManager, Enemy* enemy)
	:
	m_view{},
	m_projection{},
	m_eye{},
	m_target{ TARGET },
	m_up{ DirectX::SimpleMath::Vector3::UnitY },
	m_angle{},
	m_enemy{enemy},
	m_cameraManager{cameraManager}
{

	CalculateEyePosition();
	CalculateViewMatrix();
	CalculateProjectionMatrix();
}

void mylib::GameEndCamera::Initialize()
{
	m_angle = 0;
	m_target = m_enemy->GetPos();
}

//-------------------------------------------------------------------
// 更新する
//-------------------------------------------------------------------
void mylib::GameEndCamera::Update(const float& elapsedTime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	m_target = m_enemy->GetPos();


	// カメラ座標を計算する
	CalculateEyePosition();
	// ビュー行列を更新する
	CalculateViewMatrix();

}




//-------------------------------------------------------------------
// ビュー行列を計算する
//-------------------------------------------------------------------
void mylib::GameEndCamera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

//-------------------------------------------------------------------
// プロジェクション行列を計算する
//-------------------------------------------------------------------
void mylib::GameEndCamera::CalculateProjectionMatrix()
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
void mylib::GameEndCamera::CalculateEyePosition()
{


	// 既定の進行方向ベクトル
	DirectX::SimpleMath::Vector3 forward = m_enemy->Getforward();

	// カメラがターゲットからどれくらい離れているか
	forward = DirectX::SimpleMath::Vector3(-6,4,15);

	//敵の回転を取得
	DirectX::SimpleMath::Quaternion enemyRotate = m_enemy->GetRotate();

	// ターゲットの向いている方向に対応させる
	forward = DirectX::SimpleMath::Vector3::Transform(forward, enemyRotate);
	// カメラ座標を計算する
	m_eye = m_target + forward;

}



void mylib::GameEndCamera::Enter()
{
}


void mylib::GameEndCamera::Exit()
{

}

