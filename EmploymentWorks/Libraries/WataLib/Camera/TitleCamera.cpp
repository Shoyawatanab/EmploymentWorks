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




//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
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

void WataLib::TitleCamera::Initialize(CommonResources* resources)
{
	UNREFERENCED_PARAMETER(resources);


	CalculateEyePosition();
	CalculateViewMatrix();
	CalculateProjectionMatrix();
}

//-------------------------------------------------------------------
// 更新する
//-------------------------------------------------------------------
void WataLib::TitleCamera::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();


	// カメラ座標を計算する
	CalculateEyePosition();
	// ビュー行列を更新する
	CalculateViewMatrix();




}

//-------------------------------------------------------------------
// ビュー行列を計算する
//-------------------------------------------------------------------
void WataLib::TitleCamera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

//-------------------------------------------------------------------
// プロジェクション行列を計算する
//-------------------------------------------------------------------
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

//-------------------------------------------------------------------
// カメラ座標を計算する
//-------------------------------------------------------------------
void WataLib::TitleCamera::CalculateEyePosition()
{

	m_angle += 0.005f;
	float x = 6.0f * cosf(m_angle);
	float z = 6.0f * sinf(m_angle);

	m_eye = DirectX::SimpleMath::Vector3(x, 4.0f, z);



}



void WataLib::TitleCamera::Enter()
{
}


void WataLib::TitleCamera::Exit()
{

}

void WataLib::TitleCamera::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	assert(&view);
	assert(&projection);



}

