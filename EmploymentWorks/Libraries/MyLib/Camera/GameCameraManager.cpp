/*
	@file	GameCameraManager.cpp
	@brief	TPSカメラクラス
*/
#include "pch.h"
#include "GameCameraManager.h"
#include "Game/Screen.h"
#include "Game/Object/Player/Player.h"
#include "Libraries/MyLib/Mouse.h"

#include "Libraries/MyLib/Camera/GameStartCamera.h"
//#include "Libraries/MyLib/Camera/TPS_Camera.h"
#include "Libraries/MyLib/Camera/GameEndCamera.h"
#include "Game/Scene/PlayScene.h"

const POINT MOUSESENSITIVITY = { static_cast<LONG> (0.001f),static_cast<LONG> (0.001f) };      // マウスの感度
const int MAXANGLEY = 100;

const float EXPANSIOOSPEED = 0.7f;   //拡大時のスピード

//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
mylib::GameCameraManager::GameCameraManager()
	:
	m_currentState{},
	m_fpsCamera{},
	m_startCamera{},
	m_player{ },
	m_enemy{},
	m_playScene{}
{
}


void mylib::GameCameraManager::Initialize()
{

	m_fpsCamera->Initialize();
	m_startCamera->Initialize();
	m_endCamera->Initialize();


	DirectX::SimpleMath::Vector3 Pos;

	Pos = m_fpsCamera->GetEyePosition();
	//TPSカメラのスタート位置をスタートカメラの終点にする
	m_startCamera->SetCameraEndPos(Pos);

	m_currentState = m_startCamera.get();
	//m_currentState = m_tpsCamera.get();
	//m_currentState = m_endCamera.get();
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

	if (m_currentState == m_startCamera.get() && m_startCamera->GetLerpTime() >= 1)
	{
		ChangeState(m_fpsCamera.get());
	}


}


void mylib::GameCameraManager::ChangeState(IGameCamera* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();

}

void mylib::GameCameraManager::RegistrationInformation(PlayScene* playScene, Player* Player, Enemy* enemy)
{

	m_playScene = playScene;
	m_player = Player;
	m_enemy = enemy;

	m_fpsCamera->RegistrationInformation(m_player);
	m_startCamera->RegistrationInformation(m_player);
	m_endCamera->RegistrationInformation(this, m_enemy);

}

void mylib::GameCameraManager::Instances()
{

	m_fpsCamera = std::make_unique<mylib::FPS_Camera>();
	m_startCamera = std::make_unique<mylib::GameStartCamera>();
	m_endCamera = std::make_unique<mylib::GameEndCamera>();


}

