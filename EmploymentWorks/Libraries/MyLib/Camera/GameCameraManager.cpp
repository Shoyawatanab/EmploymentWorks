/*
	@file	GameCameraManager.cpp
	@brief	TPSカメラクラス
*/
#include "pch.h"
#include "GameCameraManager.h"
#include "Game/Screen.h"
#include "Game/Object/Player.h"
#include "Libraries/MyLib/Mouse.h"

#include "Libraries/MyLib/Camera/GameStartCamera.h"
#include "Libraries/MyLib/Camera/TPS_Camera.h"

const POINT MOUSESENSITIVITY = { 0.001f,0.001f };      // マウスの感度
const int MAXANGLEY = 100;

const float EXPANSIOOSPEED = 0.7f;   //拡大時のスピード

//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
mylib::GameCameraManager::GameCameraManager(Player* player)
	:
	m_currentState{},
	m_tpsCamera{},
	m_startCamera{},
	m_player{player}
{
}


void mylib::GameCameraManager::Initialize()
{
	m_tpsCamera = std::make_unique<mylib::TPS_Camera>(m_player);
	m_startCamera = std::make_unique<mylib::GameStartCamera>(m_player);

	m_tpsCamera->Initialize();
	m_startCamera->Initialize();

	DirectX::SimpleMath::Vector3 TPSPos = m_tpsCamera->GetEyePosition();
	DirectX::SimpleMath::Vector3 PlayerPos = m_player->GetPosition();

	DirectX::SimpleMath::Vector3 Pos = DirectX::SimpleMath::Vector3(PlayerPos.x,TPSPos.y,PlayerPos.z + TPSPos.z);

	Pos = m_tpsCamera->GetEyePosition();
	//TPSカメラのスタート位置をスタートカメラの終点にする
	m_startCamera->SetCameraEndPos(Pos);

	m_currentState = m_startCamera.get();
	//m_currentState = m_tpsCamera.get();
}

//-------------------------------------------------------------------
// 更新する
//-------------------------------------------------------------------
void mylib::GameCameraManager::Update(float elapsedTime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();

	m_currentState->Update(elapsedTime);

	if (m_startCamera->GetLerpTime() >= 1)
	{
		ChangeState(m_tpsCamera.get());
	}

}


void mylib::GameCameraManager::ChangeState(IGameCamera* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();

}
