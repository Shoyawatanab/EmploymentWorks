#include "pch.h"
#include "GameOverUI.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"
#include "Libraries/WataLib/DrawTexture.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameOverUI::GameOverUI()
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
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameOverUI::~GameOverUI()
{
}

void GameOverUI::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{


	for (int i = 0; i < m_playerHPCount; i ++)
	{
		m_playerHP[i]->Render();
	}

	for (int i = 0; i < m_boomerangCount; i++)
	{
		m_boomerang[i]->Render();
	}

	for (auto& enemyHP : m_enemyHPBase)
	{
		enemyHP->Render();

	}

	m_enemyHP->Render();

}



void GameOverUI::AddPointer(Player* player)
{
	m_player = player;
}

std::unique_ptr<UserInterface> GameOverUI::AddTexture(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
{
	//  ���j���[�Ƃ��ăA�C�e����ǉ�����
	std::unique_ptr<UserInterface> userInterface = std::make_unique<UserInterface>();
	//  �w�肳�ꂽ�摜��\�����邽�߂̃A�C�e�����쐬����
	userInterface->Create(m_commonResources->GetDeviceResources()
		, path
		, position
		, scale
		, anchor
		, kind);

	userInterface->SetWindowSize(m_windowSize.first, m_windowSize.second);


	return userInterface;
}

void GameOverUI::CreateEnemyHP()
{

	m_enemyHPBase.push_back(AddTexture(L"Resources/Textures/BossHPBase.png"
		, Vector2(640, 50)
		, Vector2(0.9f, 0.5f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI));

	m_enemyHP = AddTexture(L"Resources/Textures/EnemyHP.png"
		, Vector2(640, 50)
		, Vector2(0.91f, 0.39f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

	m_enemyHPBase.push_back(AddTexture(L"Resources/Textures/EnemyName.png"
		, Vector2(640, 25)
		, Vector2(0.3f, 0.3f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI));



}

void GameOverUI::CreatePlayerHP()
{

	for (int i = 0; i < HP_COUNT; i++)
	{
		auto texture = std::make_unique<WataLib::DrawTexture>();
		texture->Initialize(m_commonResources, L"Resources/Textures/HP.png"
			, HP_POSITION + (HP_POSITION_OFFSET * i), HP_SCALE);

		m_playerHP.push_back(std::move(texture));
	}

}

void GameOverUI::CreateBoomerang()
{

	for (int i = 0; i < BOOMERANG_COUNT; i++)
	{
		auto texture = std::make_unique<WataLib::DrawTexture>();
		texture->Initialize(m_commonResources, L"Resources/Textures/BoomerangUI.png"
			, BOOMERANG_POSITION + (BOOMERANG_POSITION_OFFSET * i), BOOMERANG_SCALE);

		m_boomerang.push_back(std::move(texture));
	}


}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void GameOverUI::Initialize(CommonResources* resources)
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

	EventManager::AddObserver(EventManager::EventTypeName::BoomerangThrow, this);
	EventManager::AddObserver(EventManager::EventTypeName::GetBoomerang, this);


}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void GameOverUI::Update(const float& elapsedTime)
{

	

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void GameOverUI::Enter()
{



}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void GameOverUI::Exit()
{
}

void GameOverUI::Notify(EventManager::EventTypeName type)
{

	switch (type)
	{
		case EventManager::EventTypeName::BoomerangThrow:
			m_boomerangCount--;
			break;
		case EventManager::EventTypeName::GetBoomerang:
			m_boomerangCount ++;
			break;
		default:
			break;
	}

}




