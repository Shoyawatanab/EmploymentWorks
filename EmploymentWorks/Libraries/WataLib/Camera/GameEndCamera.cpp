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



/// <summary>
/// コンストラクタ
/// </summary>
WataLib::GameEndCamera::GameEndCamera()
	:
	m_view{},
	m_projection{},
	m_eye{},
	m_target{ TARGET },
	m_up{ DirectX::SimpleMath::Vector3::UnitY },
	m_angle{}
	,m_rotation{}
	,m_enemyManager{}
{

}

void WataLib::GameEndCamera::AddPointer(EnemyManager* enemyManger)
{
	m_enemyManager = enemyManger;
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">経過時間</param>
void WataLib::GameEndCamera::Initialize(CommonResources* resources)
{
	UNREFERENCED_PARAMETER(resources);
	m_angle = 0;

	CalculateEyePosition();
	CalculateViewMatrix();
	CalculateProjectionMatrix();

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void WataLib::GameEndCamera::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	// カメラ座標を計算する
	CalculateEyePosition();
	// ビュー行列を更新する
	CalculateViewMatrix();

}




/// <summary>
/// ビュー行列の計算
/// </summary>
void WataLib::GameEndCamera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

/// <summary>
/// 射影行列の計算
/// </summary>
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

/// <summary>
/// カメラ座標の計算
/// </summary>
void WataLib::GameEndCamera::CalculateEyePosition()
{

	// 既定の進行方向ベクトル
	DirectX::SimpleMath::Vector3 forward;

	// ターゲットの向いている方向に対応させる
	forward = DirectX::SimpleMath::Vector3::Transform(DISTANCE_TO_TARGET, m_rotation);
	// カメラ座標を計算する
	m_eye = m_target + forward;

}

/// <summary>
/// 状態に入った時
/// </summary>
void WataLib::GameEndCamera::Enter()
{

	m_target = m_enemyManager->GetLastEnemy()->GetPosition();
	
	m_rotation = m_enemyManager->GetLastEnemy()->GetRotation();

}

/// <summary>
/// 状態を抜けた時
/// </summary>
void WataLib::GameEndCamera::Exit()
{

}

void WataLib::GameEndCamera::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);


}

