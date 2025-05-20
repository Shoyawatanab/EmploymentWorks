/*
	@file	CameraManager.cpp
	@brief	TPS�J�����N���X
*/
#include "pch.h"
#include "CameraManager.h"
#include "Game/Screen.h"

#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Libraries/WataLib/Camera/GameEndCamera.h"
#include "Game/Observer/Messenger.h"

const POINT MOUSESENSITIVITY = { static_cast<LONG> (0.001f),static_cast<LONG> (0.001f) };      // �}�E�X�̊��x
const int MAXANGLEY = 100;

const float EXPANSIOOSPEED = 0.7f;   //�g�厞�̃X�s�[�h

/// <summary>
/// �R���X�g���N�^
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
/// �f�X�g���N�^
/// </summary>
WataLib::CameraManager::~CameraManager()
{
}


/// <summary>
/// ������
/// </summary>
/// <param name="resources">�o�ߎ���</param>
void WataLib::CameraManager::Initialize(CommonResources* resources)
{

	m_tpsCamera->Initialize(resources);
	m_endCamera->Initialize(resources);

	m_currentState = m_tpsCamera.get();


	//���b�Z�[�W�N���X�ɓo�^
	Messenger::GetInstance()->Rigister(GameMessageType::DEFEATED_All_ENEMIES, this);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void WataLib::CameraManager::Update(float elapsedTime)
{

	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();

	m_currentState->Update(elapsedTime);



}

/// <summary>
/// �X�e�[�g�̐؂�ւ�
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
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="telegram">�f�[�^</param>
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


