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

/// <summary>
/// コンストラクタ
/// </summary>
WataLib::CameraManager::CameraManager()
	:
	m_currentState{},
	m_tpsCamera{},
	m_player{ }
{
	m_tpsCamera = std::make_unique<WataLib::TPS_Camera>();
	m_endCamera = std::make_unique<WataLib::GameEndCamera>();
}


/// <summary>
/// デストラクタ
/// </summary>
WataLib::CameraManager::~CameraManager()
{
}


/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">経過時間</param>
void WataLib::CameraManager::Initialize(CommonResources* resources)
{

	m_tpsCamera->Initialize(resources);
	m_endCamera->Initialize(resources);

	m_currentState = m_tpsCamera.get();


	//メッセージクラスに登録
	Messenger::GetInstance()->Rigister(GameMessageType::DEFEATED_All_ENEMIES, this);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void WataLib::CameraManager::Update(float elapsedTime)
{

	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();

	m_currentState->Update(elapsedTime);



}

/// <summary>
/// ステートの切り替え
/// </summary>
/// <param name="nextState"></param>
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

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="telegram">データ</param>
void WataLib::CameraManager::Notify(const Telegram<GameMessageType>& telegram)
{
	
	switch (telegram.messageType)
	{
		case GameMessageType::DEFEATED_All_ENEMIES:
			ChangeState(m_endCamera.get());
			break;
		default:
			break;
	}
}


