/*
	@file	CameraManager.cpp
	@brief	TPSカメラクラス
*/
#include "pch.h"
#include "CameraManager.h"
#include "Game/Screen.h"

#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Libraries/WataLib/Camera/GameEndCamera.h"
#include "Game/Observer/Messenger.h"

const POINT MOUSESENSITIVITY = { static_cast<LONG> (0.001f),static_cast<LONG> (0.001f) };      // マウスの感度
const int MAXANGLEY = 100;

const float EXPANSIOOSPEED = 0.7f;   //拡大時のスピード

//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
WataLib::CameraManager::CameraManager()
	:
	m_currentState{},
	m_tpsCamera{},
	m_player{ }
{
	m_tpsCamera = std::make_unique<WataLib::TPS_Camera>();
	m_endCamera = std::make_unique<WataLib::GameEndCamera>();
}


WataLib::CameraManager::~CameraManager()
{
}

void WataLib::CameraManager::Initialize(CommonResources* resources)
{

	m_tpsCamera->Initialize(resources);
	m_endCamera->Initialize(resources);

	m_currentState = m_tpsCamera.get();



	Messenger::GetInstance()->Attach(MessageType::DefeatedAllEnemies, this);
}

//-------------------------------------------------------------------
// 更新する
//-------------------------------------------------------------------
void WataLib::CameraManager::Update(float elapsedTime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();

	m_currentState->Update(elapsedTime);



}


void WataLib::CameraManager::ChangeState(ICamera* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();

}

void WataLib::CameraManager::AddPointer(Player* Player, EnemyManager* enemyManger)
{

	m_player = Player;
	//m_enemy = enemy;

	m_tpsCamera->AddPointer(m_player);
	m_endCamera->AddPointer(enemyManger);
}

void WataLib::CameraManager::Notify(const Telegram& telegram)
{
	
	switch (telegram.messageType)
	{
		case MessageType::DefeatedAllEnemies:
			ChangeState(m_endCamera.get());
			break;
		default:
			break;
	}
}


