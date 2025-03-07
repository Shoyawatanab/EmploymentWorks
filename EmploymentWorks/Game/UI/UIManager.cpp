/*
	@file	UIManager.cpp
	@brief	
*/
#include "pch.h"
#include "UIManager.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include <cassert>
#include "Game/UI/State/UIStateMachine.h"
#include "Game/Observer/Messenger.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
UIManager::UIManager()
	:
	m_commonResources{}
	,m_stateMahine{}
{
	m_stateMahine = std::make_unique<UIStateMachine>();
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
UIManager::~UIManager()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void UIManager::Initialize(CommonResources* resources)
{
	using namespace DirectX::SimpleMath;
	assert(resources);
	m_commonResources = resources;

	m_stateMahine->Initialize(m_commonResources, m_stateMahine->GetGamePlayUI());

	Messenger::Attach(EventParams::EventType::GameClear, this);
	Messenger::Attach(EventParams::EventType::GameOver, this);

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void UIManager::Update(const float& elapsedTime)
{

	m_stateMahine->Update(elapsedTime);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void UIManager::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	using namespace DirectX::SimpleMath;

	m_stateMahine->Render(view, projection);

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void UIManager::Finalize()
{
	// do nothing.
}

/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="player">�v���C��</param>
/// <param name="playScene">�v���C�V�[��</param>
/// <param name="enemyManager">�G�l�~�[�}�l�[�W���[</param>
void UIManager::AddPointer(Player* player, PlayScene* playScene, EnemyManager* enemyManager)
{

	m_stateMahine->AddPointer(player,playScene,enemyManager);

}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�C�x���g�̎��</param>
/// <param name="datas">�C�x���g�̃f�[�^</param>
void UIManager::Notify(EventParams::EventType type, void* datas)
{
	switch (type)
	{
		case EventParams::EventType::GameClear:
			m_stateMahine->ChangeState(m_stateMahine->GetGameEndUI());
			m_stateMahine->GetGameEndUI()->SetBackGraund(true);
			break;
		case EventParams::EventType::GameOver:
			m_stateMahine->ChangeState(m_stateMahine->GetGameEndUI());
			m_stateMahine->GetGameEndUI()->SetBackGraund(false);

			break;
		default:
			break;
	}
}




