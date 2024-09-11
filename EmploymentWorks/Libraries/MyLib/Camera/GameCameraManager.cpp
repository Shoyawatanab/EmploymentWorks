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
#include "Libraries/MyLib/Camera/TPS_Camera.h"
#include "Libraries/MyLib/Camera/GameEndCamera.h"
#include "Game/Scene/PlayScene.h"

const POINT MOUSESENSITIVITY = { 0.001f,0.001f };      // マウスの感度
const int MAXANGLEY = 100;

const float EXPANSIOOSPEED = 0.7f;   //拡大時のスピード

//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
mylib::GameCameraManager::GameCameraManager(PlayScene* playScene, Player* player, Enemy* enemy)
	:
	m_currentState{},
	m_tpsCamera{},
	m_startCamera{},
	m_player{ player },
	m_enemy{ enemy },
	m_playScene{ playScene }
{
}


void mylib::GameCameraManager::Initialize()
{
	m_tpsCamera = std::make_unique<mylib::TPS_Camera>(m_player);
	m_startCamera = std::make_unique<mylib::GameStartCamera>(m_player);
	m_endCamera = std::make_unique<mylib::GameEndCamera>(this, m_enemy);

	m_tpsCamera->Initialize();
	m_startCamera->Initialize();
	m_endCamera->Initialize();


	DirectX::SimpleMath::Vector3 TPSPos = m_tpsCamera->GetEyePosition();
	DirectX::SimpleMath::Vector3 PlayerPos = m_player->GetPosition();

	DirectX::SimpleMath::Vector3 Pos = DirectX::SimpleMath::Vector3(PlayerPos.x, TPSPos.y, PlayerPos.z + TPSPos.z);

	Pos = m_tpsCamera->GetEyePosition();
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
		ChangeState(m_tpsCamera.get());
	}


}


void mylib::GameCameraManager::ChangeState(IGameCamera* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();

}

void mylib::GameCameraManager::GameEnd()
{
	m_playScene->SetNextSceneID(PlayScene::SceneID::RESULT);
}
