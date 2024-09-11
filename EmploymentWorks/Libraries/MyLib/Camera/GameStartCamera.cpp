/*
	@file	GameStartCamera.cpp
	@brief	TPSカメラクラス
*/
#include "pch.h"
#include "GameStartCamera.h"
#include "Game/Screen.h"
#include "Game/Object/Player/Player.h"
#include "Libraries/MyLib/Mouse.h"

const int MAXANGLEY = 100;
const DirectX::SimpleMath::Vector3 TARGET = DirectX::SimpleMath::Vector3(0, 1, 0); //ステージの中心

const float MOVESPEED = 0.5f;
DirectX::SimpleMath::Vector3 STARTPOS = DirectX::SimpleMath::Vector3(0, 15, 25);



float Lerp(const float& start, const float& end, const float& t)
{
	return (1.0f - t) * start + t * end;
}

DirectX::SimpleMath::Vector3 Lerp(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end, float t)
{
	//return start + t * (end - start);
	return (1.0f - t) * start + t * end;
}

inline float Clamp(const float& value, const float& min, const float& max)
{
	if (value < min) 	return min;
	else if (value > max) return max;
	return value;
}

//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
mylib::GameStartCamera::GameStartCamera(Player* player)
	:
	m_view{},
	m_projection{},
	m_eye{},
	m_target{ TARGET },
	m_up{ DirectX::SimpleMath::Vector3::UnitY },
	m_player{ player },
	m_lerpTime{},
	m_angle{},
	m_height{},
	m_distanceFromTarget{},
	m_cameraEndPos{},
	m_endTarget{}
{

	CalculateEyePosition();
	CalculateViewMatrix();
	CalculateProjectionMatrix();
}

void mylib::GameStartCamera::Initialize()
{
	m_angle = 0;
	m_height = STARTPOS.y;
	m_distanceFromTarget = STARTPOS.z;
	m_target = m_player->GetPosition();
	m_target = TARGET;
	m_lerpTime = 0;
	m_endTarget = m_player->GetPosition();
}

//-------------------------------------------------------------------
// 更新する
//-------------------------------------------------------------------
void mylib::GameStartCamera::Update(const float& elapsedTime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();

	m_distanceFromTarget = Lerp(STARTPOS.z, m_cameraEndPos.z, m_lerpTime);
	m_height = Lerp(STARTPOS.y, m_cameraEndPos.y, m_lerpTime);
	m_target = Lerp(TARGET, m_endTarget, m_lerpTime);


	// カメラ座標を計算する
	CalculateEyePosition();
	// ビュー行列を更新する
	CalculateViewMatrix();

	m_lerpTime += 0.01f;
	m_lerpTime = Clamp(m_lerpTime, 0, 1);



}

//-------------------------------------------------------------------
// ビュー行列を計算する
//-------------------------------------------------------------------
void mylib::GameStartCamera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

//-------------------------------------------------------------------
// プロジェクション行列を計算する
//-------------------------------------------------------------------
void mylib::GameStartCamera::CalculateProjectionMatrix()
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
void mylib::GameStartCamera::CalculateEyePosition()
{

	//m_angle += 0.01f;
	//m_angle = 1.55f;
	float x = m_distanceFromTarget * cosf(m_angle);
	float z = m_distanceFromTarget * sinf(m_angle);

	m_eye = DirectX::SimpleMath::Vector3(0, m_height, m_distanceFromTarget);

}



void mylib::GameStartCamera::Enter()
{
}


void mylib::GameStartCamera::Exit()
{

}

