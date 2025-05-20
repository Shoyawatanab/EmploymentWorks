/*
	@file	TitleCamera.cpp
	@brief	TPSカメラクラス
*/
#include "pch.h"
#include "TitleCamera.h"
#include "Game/Screen.h"


const int MAXANGLEY = 100;
const DirectX::SimpleMath::Vector3 TARGET = DirectX::SimpleMath::Vector3(0, 1, 0); //ステージの中心

const float MOVESPEED = 0.5f;




/// <summary>
/// コンストラクタ
/// </summary>
WataLib::TitleCamera::TitleCamera()
	:
	m_view{},
	m_projection{},
	m_eye{},
	m_target{ TARGET },
	m_up{ DirectX::SimpleMath::Vector3::UnitY },
	m_angle{}
{


}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void WataLib::TitleCamera::Initialize(CommonResources* resources)
{
	UNREFERENCED_PARAMETER(resources);


	CalculateEyePosition(0);
	CalculateViewMatrix();
	CalculateProjectionMatrix();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void WataLib::TitleCamera::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();


	// カメラ座標を計算する
	CalculateEyePosition(elapsedTime);
	// ビュー行列を更新する
	CalculateViewMatrix();




}

/// <summary>
// ビュー行列の計算
/// </summary>
void WataLib::TitleCamera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

/// <summary>
/// プロジェクション行列の計算
/// </summary>
void WataLib::TitleCamera::CalculateProjectionMatrix()
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
void WataLib::TitleCamera::CalculateEyePosition(const float& elapsedTime)
{

	m_angle += ROTATION_SPEED * elapsedTime;
	float x = DISTANCE_TO_TARGET.x * cosf(m_angle);
	float z = DISTANCE_TO_TARGET.z * sinf(m_angle);

	m_eye = DirectX::SimpleMath::Vector3(x, DISTANCE_TO_TARGET.y, z);

}


/// <summary>
/// 状態に入った時
/// </summary>
void WataLib::TitleCamera::Enter()
{
}

/// <summary>
/// 状態を抜けた時
/// </summary>
void WataLib::TitleCamera::Exit()
{

}

void WataLib::TitleCamera::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	assert(&view);
	assert(&projection);



}

