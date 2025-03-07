/*
	@file	GameEndCamera.cpp
	@brief	TPSカメラクラス
*/
#include "pch.h"
#include "GameEndCamera.h"
#include "Game/Screen.h"
#include "Game/Enemys/EnemyManager.h"

const DirectX::SimpleMath::Vector3 TARGET = DirectX::SimpleMath::Vector3(0, 1, 0); //ステージの中心

const float MAXTIME = 4;



//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
WataLib::GameEndCamera::GameEndCamera()
	:
	m_view{},
	m_projection{},
	m_eye{},
	m_target{ TARGET },
	m_up{ DirectX::SimpleMath::Vector3::UnitY },
	m_angle{},
	m_character{}
	,m_rotation{}
{

}

void WataLib::GameEndCamera::AddPointer(EnemyManager* enemyManger)
{
	m_enemyManager = enemyManger;
}

void WataLib::GameEndCamera::Initialize(CommonResources* resources)
{
	m_angle = 0;

	CalculateEyePosition();
	CalculateViewMatrix();
	CalculateProjectionMatrix();

}

//-------------------------------------------------------------------
// 更新する
//-------------------------------------------------------------------
void WataLib::GameEndCamera::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	using namespace DirectX;
	using namespace DirectX::SimpleMath;



	// カメラ座標を計算する
	CalculateEyePosition();
	// ビュー行列を更新する
	CalculateViewMatrix();

}




//-------------------------------------------------------------------
// ビュー行列を計算する
//-------------------------------------------------------------------
void WataLib::GameEndCamera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

//-------------------------------------------------------------------
// プロジェクション行列を計算する
//-------------------------------------------------------------------
void WataLib::GameEndCamera::CalculateProjectionMatrix()
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
void WataLib::GameEndCamera::CalculateEyePosition()
{

	// 既定の進行方向ベクトル
	DirectX::SimpleMath::Vector3 forward;

	// カメラがターゲットからどれくらい離れているか
	forward = DirectX::SimpleMath::Vector3(-6,4,15);

	// ターゲットの向いている方向に対応させる
	forward = DirectX::SimpleMath::Vector3::Transform(forward, m_rotation);
	// カメラ座標を計算する
	m_eye = m_target + forward;

}


void WataLib::GameEndCamera::Enter()
{

	m_target = m_enemyManager->GetLastEnemy()->GetPosition();
	
	m_rotation = m_enemyManager->GetLastEnemy()->GetRotation();

}


void WataLib::GameEndCamera::Exit()
{

}

void WataLib::GameEndCamera::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
}

