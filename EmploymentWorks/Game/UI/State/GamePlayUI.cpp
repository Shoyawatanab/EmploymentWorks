#include "pch.h"
#include "GamePlayUI.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"
#include "Game/Observer/Messenger.h"
#include "Libraries/WataLib/DamageCountUI.h"
#include "Libraries/WataLib/GameResources.h"
#include "Game/Params.h"
#include "Game/InstanceRegistry.h"
#include "Game/UI/ThrowQuantity.h"
#include "Game/UI/BossEnemyHP.h"


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
	, m_itemAcquisitionUI{}
	,m_throwUI{}
	,m_throwQuantityUI{}
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



	for (auto& throwUI : m_throwUI)
	{
		throwUI->Render();
	}

	m_throwQuantityUI->Render();

	m_itemAcquisitionUI->Render();

	for (auto& da : m_damageCountUI)
	{
		da->Render(view,projection);
	}

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
/// �v���C��HP�̍쐬
/// </summary>
void GamePlayUI::CreatePlayerHP()
{

	for (int i = 0; i < HP_COUNT; i++)
	{
		auto texture = std::make_unique<UserInterface>();
		texture->Create(m_commonResources, "HP"
			, HP_POSITION + (HP_POSITION_OFFSET * static_cast<float>(i)), HP_SCALE);

		m_playerHP.push_back(std::move(texture));
	}

}

/// <summary>
/// �u�[�������c�@�̐���
/// </summary>
void GamePlayUI::CreateBoomerang()
{

	for (int i = 0; i < Params::BOOMERANG_MAX_COUNT; i++)
	{
		auto texture = std::make_unique<UserInterface>();
		texture->Create(m_commonResources, "BoomerangUI"
			, BOOMERANG_POSITION + (BOOMERANG_POSITION_OFFSET * static_cast<float>(i)), BOOMERANG_SCALE);

		m_boomerang.push_back(std::move(texture));
	}


}

void GamePlayUI::CreateDamageUI(void* datas)
{

	UnknownDataThree* data = static_cast<UnknownDataThree*>(datas);


	for (auto& damageCount : m_damageCountUI)
	{
		if (!damageCount->GetIsActive())
		{
			damageCount->SetIsActive(true);

			damageCount->SetPosition(*static_cast<DirectX::SimpleMath::Vector3*>(data->data1));

			//damageCount->SetDamage(*static_cast<int*>(data->data3));
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

	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");

	//��ʃT�C�Y�̎擾
	m_windowSize.first = m_commonResources->GetDeviceResources()->GetOutputSize().right;
	m_windowSize.second = m_commonResources->GetDeviceResources()->GetOutputSize().bottom;

	m_playerHPCount = HP_COUNT;

	m_boomerangCount = Params::BOOMERANG_MAX_COUNT;

	CreatePlayerHP();
	CreateBoomerang();

	m_itemAcquisitionUI = AddTexture("F"
		, Vector2(750, 600)
		, Vector2(0.15f, 0.15f)
		);

	m_itemAcquisitionUI->SetIsActive(false);

	m_throwUI.push_back(AddTexture("RightThrow"
		, RIGHT_THROW_POSITION
		, RIGHT_THROW_SCALE
		));

	m_throwUI.push_back(AddTexture("FrontThrow"
		, FRONT_THROW_POSITION
		, FRONT_THROW_SCALE
		));

	m_throwUI.push_back(AddTexture("LeftThrow"
		, LEFT_THROW_POSITION
		, LEFT_THROW_SCALE
		));

	m_throwUI[0]->SetPosition(m_throwUI[0]->GetInitialPosition() + MOVEPOSITION);


	for (int i = 0; i < MAXDAMAGEUICOUNT; i++)
	{
		auto dameUi = std::make_unique<WataLib::DamageCountUI>(m_commonResources);
		dameUi->Initialize();

		m_damageCountUI.push_back(std::move(dameUi));

	}

	Messenger::GetInstance()->Rigister(GamePlayMessageType::BOOMERANG_THTROW, this);
	Messenger::GetInstance()->Rigister(GamePlayMessageType::GET_BOOMERANG, this);
	Messenger::GetInstance()->Rigister(GamePlayMessageType::PLAYER_DAMAGE, this);
	Messenger::GetInstance()->Rigister(GamePlayMessageType::CHARGE_BOOMERANG_THROW_STATE, this);
	Messenger::GetInstance()->Rigister(GamePlayMessageType::BOOMERANG_RECOVERBLE, this);
	Messenger::GetInstance()->Rigister(GamePlayMessageType::BOOMERANG_NOT_RECOVERBLE, this);

	Messenger::GetInstance()->Rigister(GamePlayMessageType::CREATE_HIT_EFFECT, this);

	m_throwQuantityUI = std::make_unique<ThrowQuantity>(m_commonResources);
	m_throwQuantityUI->Initialize();

	m_bossEnemyHP = std::make_unique<BossEnemyHP>(m_commonResources);
	m_bossEnemyHP->Initialize();


}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void GamePlayUI::Update(const float& elapsedTime)
{



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
void GamePlayUI::Notify(const Telegram<GamePlayMessageType>& telegram)
{

	switch (telegram.messageType)
	{
		case GamePlayMessageType::BOOMERANG_THTROW:
		{

			int value = *static_cast<int*>(telegram.extraInfo);
			m_boomerangCount-= value;

			m_boomerangCount = std::max(m_boomerangCount, 0);
		}
			break;
		case GamePlayMessageType::GET_BOOMERANG:
		{

			int value = *static_cast<int*>(telegram.extraInfo);
			m_boomerangCount+= value;
			m_boomerangCount = std::min(m_boomerangCount, Params::BOOMERANG_MAX_COUNT);

		}


			break;
		case GamePlayMessageType::PLAYER_DAMAGE:
			m_playerHPCount--;
			break;
		case GamePlayMessageType::CHARGE_BOOMERANG_THROW_STATE:
			{
				
				switch (*static_cast<int*>(telegram.extraInfo))
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
		case GamePlayMessageType::BOOMERANG_RECOVERBLE:
			m_itemAcquisitionUI->SetIsActive(true);
			break;
		case GamePlayMessageType::BOOMERANG_NOT_RECOVERBLE:
			m_itemAcquisitionUI->SetIsActive(false);
			break;
		case GamePlayMessageType::CREATE_HIT_EFFECT:
			CreateDamageUI(telegram.extraInfo);
			break;
		default:
			break;
	}
}




void GamePlayUI::PlayerDamage()
{
}









