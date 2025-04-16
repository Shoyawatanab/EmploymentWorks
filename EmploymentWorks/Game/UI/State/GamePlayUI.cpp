#include "pch.h"
#include "GamePlayUI.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"
#include "Game/Enemys/EnemyManager.h"
#include "Game/Observer/Messenger.h"
#include "Libraries/WataLib/DamageCountUI.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
GamePlayUI::GamePlayUI()
	:
	m_commonResources{}
	,m_position{}
	,m_scale{}
	,m_rotation{}
	,m_player{}
	,m_playerHP{}
	,m_boomerang{}
	,m_windowSize{}
	,m_playerHPCount{}
	,m_boomerangCount{}
	,m_enemyHP{}
	,m_enemyHPBase{}
	, m_itemAcquisitionUI{}
	,m_throwUI{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GamePlayUI::~GamePlayUI()
{
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void GamePlayUI::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{


	for (int i = 0; i < m_playerHPCount; i ++)
	{
		m_playerHP[i]->Render();
	}

	for (int i = 0; i < m_boomerangCount; i++)
	{
		m_boomerang[i]->Render();
	}

	if (m_enemyManager->GetBossEnemy() != nullptr)
	{
		for (auto& enemyHP : m_enemyHPBase)
		{
			enemyHP->Render();

		}

		m_enemyHP->Render();

	}

	for (auto& throwUI : m_throwUI)
	{
		throwUI->Render();
	}

	m_itemAcquisitionUI->Render();

	for (auto& da : m_damageCountUI)
	{
		da->Render(view,projection);
	}

}


/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="player">�v���C��</param>
/// <param name="enemyManager">�G�l�~�[�}�l�[�W���[</param>
void GamePlayUI::AddPointer(Player* player, EnemyManager* enemyManager)
{
	m_player = player;
	m_enemyManager = enemyManager;
}

/// <summary>
/// �摜�̒ǉ�
/// </summary>
/// <param name="path">�ǂݍ��݂̃p�X</param>
/// <param name="position">���W</param>
/// <param name="scale">�傫��</param>
/// <param name="anchor">�A���J�[</param>
/// <param name="kind">���</param>
/// <returns>UI�̃|�C���^</returns>
std::unique_ptr<UserInterface> GamePlayUI::AddTexture(std::string key, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale)
{
	//  ���j���[�Ƃ��ăA�C�e����ǉ�����
	std::unique_ptr<UserInterface> userInterface = std::make_unique<UserInterface>();
	//  �w�肳�ꂽ�摜��\�����邽�߂̃A�C�e�����쐬����
	userInterface->Create(m_commonResources
		, key
		, position
		, scale
		);


	return userInterface;
}

/// <summary>
/// �GHP�̍쐬
/// </summary>
void GamePlayUI::CreateEnemyHP()
{

	m_enemyHPBase.push_back(AddTexture("BossHPBase"
		, Vector2(640, 50)
		, Vector2(0.9f, 0.5f)
		));

	m_enemyHP = AddTexture("EnemyHP"
		, Vector2(640, 50)
		, Vector2(0.91f, 0.39f)
		);

	m_enemyHPBase.push_back(AddTexture("EnemyName"
		, Vector2(640, 25)
		, Vector2(0.3f, 0.3f)
		));



}

/// <summary>
/// �v���C��HP�̍쐬
/// </summary>
void GamePlayUI::CreatePlayerHP()
{

	for (int i = 0; i < HP_COUNT; i++)
	{
		auto texture = std::make_unique<UserInterface>();
		texture->Create(m_commonResources, "HP"
			, HP_POSITION + (HP_POSITION_OFFSET * i), HP_SCALE);

		m_playerHP.push_back(std::move(texture));
	}

}

/// <summary>
/// �u�[�������c�@�̐���
/// </summary>
void GamePlayUI::CreateBoomerang()
{

	for (int i = 0; i < BOOMERANG_COUNT; i++)
	{
		auto texture = std::make_unique<UserInterface>();
		texture->Create(m_commonResources, "BoomerangUI"
			, BOOMERANG_POSITION + (BOOMERANG_POSITION_OFFSET * i), BOOMERANG_SCALE);

		m_boomerang.push_back(std::move(texture));
	}


}

void GamePlayUI::CreateDamageUI(void* datas)
{

	EventParams::CreateHitEffectDatas* data = static_cast<EventParams::CreateHitEffectDatas*>(datas);


	for (auto& damageCount : m_damageCountUI)
	{
		if (!damageCount->GetIsActive())
		{
			damageCount->SetIsActive(true);

			damageCount->SetPosition(data->Position);

			damageCount->SetDamage(data->Damage);
			damageCount->SetDamage(10);


			break;
		}
	}




}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void GamePlayUI::Initialize(CommonResources* resources)
{
	m_commonResources = resources;

	//��ʃT�C�Y�̎擾
	m_windowSize.first = m_commonResources->GetDeviceResources()->GetOutputSize().right;
	m_windowSize.second = m_commonResources->GetDeviceResources()->GetOutputSize().bottom;

	m_playerHPCount = HP_COUNT;

	m_boomerangCount = BOOMERANG_COUNT;

	CreatePlayerHP();
	CreateBoomerang();
	CreateEnemyHP();

	m_itemAcquisitionUI = AddTexture("F"
		, Vector2(750, 600)
		, Vector2(0.15f, 0.15f)
		);

	m_itemAcquisitionUI->SetIsActive(false);

	m_throwUI.push_back(AddTexture("RightThrow"
		, Vector2(1220, 500)
		, Vector2(0.2f, 0.2f)
		));

	m_throwUI.push_back(AddTexture("FrontThrow"
		, Vector2(1220, 550)
		, Vector2(0.2f, 0.2f)
		));

	m_throwUI.push_back(AddTexture("LeftThrow"
		, Vector2(1220, 600)
		, Vector2(0.2f, 0.2f)
		));

	m_throwUI[0]->SetPosition(m_throwUI[0]->GetInitialPosition() + MOVEPOSITION);


	for (int i = 0; i < MAXDAMAGEUICOUNT; i++)
	{
		auto dameUi = std::make_unique<WataLib::DamageCountUI>(m_commonResources);
		dameUi->Initialize();

		m_damageCountUI.push_back(std::move(dameUi));

	}

	Messenger::Attach(EventParams::EventType::BoomerangThrow, this);
	Messenger::Attach(EventParams::EventType::GetBoomerang, this);
	Messenger::Attach(EventParams::EventType::PlayerDamage, this);
	Messenger::Attach(EventParams::EventType::ChangeBoomerangThrowState, this);
	Messenger::Attach(EventParams::EventType::BoomerangRecoverable, this);
	Messenger::Attach(EventParams::EventType::BoomerangNotRecoverable, this);

	Messenger::Attach(EventParams::EventType::CreateHitEffect, this);

}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void GamePlayUI::Update(const float& elapsedTime)
{

	if (m_enemyManager->GetBossEnemy() != nullptr)
	{
		m_enemyHP->SetRenderRatio(m_enemyManager->GetBossHPRation());

	}


	for (auto& da : m_damageCountUI)
	{
		da->Update(elapsedTime);
	}

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void GamePlayUI::Enter()
{



}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void GamePlayUI::Exit()
{
}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�C�x���g�̎��</param>
/// <param name="datas">�C�x���g�̃f�[�^</param>
void GamePlayUI::Notify(EventParams::EventType type, void* datas)
{

	switch (type)
	{
		case EventParams::EventType::BoomerangThrow:
			m_boomerangCount--;

			m_boomerangCount = std::max(m_boomerangCount, 0);

			break;
		case EventParams::EventType::GetBoomerang:
			m_boomerangCount++;
			m_boomerangCount = std::min(m_boomerangCount, 3);

			break;
		case EventParams::EventType::PlayerDamage:
			m_playerHPCount--;
			break;
		case EventParams::EventType::ChangeBoomerangThrowState:
			{
				EventParams::ChangeBoomerangThrowStateDatas* data = static_cast<EventParams::ChangeBoomerangThrowStateDatas*>(datas);

				switch (data->State)
				{
					case 0:

						m_throwUI[0]->SetPosition(m_throwUI[0]->GetInitialPosition() + MOVEPOSITION);
						m_throwUI[1]->SetPosition(m_throwUI[1]->GetInitialPosition());
						m_throwUI[2]->SetPosition(m_throwUI[2]->GetInitialPosition());

						break;
					case 1:
						m_throwUI[0]->SetPosition(m_throwUI[0]->GetInitialPosition());
						m_throwUI[1]->SetPosition(m_throwUI[1]->GetInitialPosition() + MOVEPOSITION);
						m_throwUI[2]->SetPosition(m_throwUI[2]->GetInitialPosition());
						break;
					case 2:
						m_throwUI[0]->SetPosition(m_throwUI[0]->GetInitialPosition());
						m_throwUI[1]->SetPosition(m_throwUI[1]->GetInitialPosition());
						m_throwUI[2]->SetPosition(m_throwUI[2]->GetInitialPosition() + MOVEPOSITION);
						break;
					default:
						break;
				}
			}
			break;
		case EventParams::EventType::BoomerangRecoverable:
			m_itemAcquisitionUI->SetIsActive(true);
			break;
		case EventParams::EventType::BoomerangNotRecoverable:
			m_itemAcquisitionUI->SetIsActive(false);
			break;
		case EventParams::EventType::CreateHitEffect:
		
			CreateDamageUI(datas);
		
			break;
		default:
			break;
	}
}

/// <summary>
/// �ʒm���󂯎��
/// </summary>
/// <param name="objectID"></param>
/// <param name="messegeId"></param>
void GamePlayUI::Notify(Message::MessageID messegeId)
{
	//���b�Z�[�WID
	switch (messegeId)
	{
		//�v���C���̃_���[�W
		case Message::PlayerDamage:
			//�֐��̌Ăяo��
			PlayerDamage();
			break;
		default:
			break;
	}
}


void GamePlayUI::PlayerDamage()
{
}







