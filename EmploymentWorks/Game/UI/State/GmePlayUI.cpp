/*
	@file	GamePlayUI.cpp
	@brief	TPS�J�����N���X
*/
#include "pch.h"
#include "Game/UI/State/GmePlayUI.h"
#include "Game/Screen.h"
#include "Game/Object/Player/Player.h"
#include "Libraries/MyLib/Mouse.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/BossEnemy.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Game/Scene/PlayScene.h"


const int MAXANGLEY = 100;
const DirectX::SimpleMath::Vector3 TARGET = DirectX::SimpleMath::Vector3(0, 1, 0); //�X�e�[�W�̒��S

const float MOVESPEED = 0.5f;




//-------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------
GamePlayUI::GamePlayUI()
	:
	m_commonResources{},
	m_windowWidth{},
	m_windowHeight{},
	m_player{},
	m_enemy{},
	m_playerHP{},
	m_enemyHP{}
{


}

void GamePlayUI::Initialize(CommonResources* resources)
{
	m_commonResources = resources;
	CreateEnemyHP();
	CreatePlayerHP();
	CreateBoomerang();

	CreateBoomerangMaker();

	//�{�XHP�̊������Z�b�g����
	float EnemyHp = m_enemy->GetHp();
	float ratio = EnemyHp / m_enemy->GetMAXHp();
	m_enemyHP[1]->SetRenderRatio(ratio);


}

//-------------------------------------------------------------------
// �X�V����
//-------------------------------------------------------------------
void GamePlayUI::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();

	//�G��HP�̎擾
	float EnemyHp = m_enemy->GetHp();
	//���������߂�
	float ratio = EnemyHp / m_enemy->GetMAXHp();
	//��������
	m_enemyHP[1]->SetRenderRatio(ratio);

	//�u�[��������UI�̍��W�������l��
	for (auto& boomerangUI : m_boomerangUI)
	{
		boomerangUI->SetPosition(boomerangUI->GetStartPosition());
	}



	//�g�p���̃u�[��������Index�����Ƃ�UI��
	//�g�p���̃u�[��������Index�̎擾
	int Index = m_player->GetUsingBoomerangIndex();
	//�g�p���̃u�[�������̂̍��W�̎擾
	DirectX::SimpleMath::Vector2 Pos = m_boomerangUI[Index]->GetStartPosition();
	//Y���W�����
	Pos.y -= 20;
	//���W�̑��
	m_boomerangUI[Index]->SetPosition(Pos);

	m_boomerangBackUI[0]->SetPosition(Pos);




}

void GamePlayUI::Render()
{

	for (auto& enemyHP : m_enemyHP)
	{
		enemyHP->Render();

	}



	for (int i = 0; i < m_player->GetPlayerHP(); i++)
	{
		m_playerHP[i]->Render();

	}

	for (auto& boomerangUI : m_boomerangUI)
	{
		boomerangUI->Render();
	}

	for (auto& boomerangBackUI : m_boomerangBackUI)
	{
		boomerangBackUI->Render();
	}


}




void GamePlayUI::Enter()
{

}


void GamePlayUI::Exit()
{

}

void GamePlayUI::RegistrationInformation(Player* player, Enemy* enemy, PlayScene* playScene)
{

	m_player = player;
	m_enemy = enemy;
	m_playScene = playScene;

}

void GamePlayUI::BoomerangMakerUpdate()
{


	DirectX::SimpleMath::Vector2 minScale(0.1f,0.1f);

	DirectX::SimpleMath::Vector2 maxScale(0.5f, 0.5f);

	//�X���[���o�̐i�s��������Lerp�̊��������߂�@�����Ă�̂̓}�[�J�[�̂ق��������������Ȃ�悤��
	float lerpTime = m_playScene->GetSlowMotionProgressRate() * 1.5f;

	m_boomerangMakerUIScale = DirectX::SimpleMath::Vector2::Lerp(maxScale, minScale,lerpTime);

	m_boomerangMakerUIScale.x = std::max(m_boomerangMakerUIScale.x, 0.1f);

	m_boomerangMakerUIScale.y = std::max(m_boomerangMakerUIScale.y, 0.1f);

	m_boomerangMarkerUI->SetScale(m_boomerangMakerUIScale);

}

void GamePlayUI::BoomerangMakerRender()
{

	m_boomerangMarkerUI->Render();

}

std::unique_ptr<UserInterface> GamePlayUI::Add(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
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

	userInterface->SetWindowSize(m_windowWidth, m_windowHeight);


	return userInterface;
}



void GamePlayUI::CreateEnemyHP()
{
	using namespace DirectX::SimpleMath;
	//  �w�i�ƂȂ�E�B���h�E�摜��ǂݍ���

	 m_enemyHP.push_back( Add(L"Resources/Textures/BossHPBase.png"
		, Vector2(640, 50)
		, Vector2(0.9f, 0.5f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI));

	m_enemyHP.push_back(Add(L"Resources/Textures/EnemyHP.png"
		, Vector2(640, 50)
		, Vector2(0.91f, 0.39f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI));

	m_enemyHP.push_back(Add(L"Resources/Textures/EnemyName.png"
		, Vector2(640, 25)
		, Vector2(0.3f, 0.3f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI));


}

void GamePlayUI::CreatePlayerHP()
{
	using namespace DirectX::SimpleMath;

	for (int i = 0; i < 3; i++)
	{
		m_playerHP.push_back(Add(L"Resources/Textures/HP.png"
			, Vector2(50 + 70 * static_cast<float>(i), 680)
			, Vector2(1.0f, 1.0f)
			, ANCHOR::MIDDLE_CENTER
			, UserInterface::Kinds::UI));
	}



}

void GamePlayUI::CreateBoomerang()
{

	using namespace DirectX::SimpleMath;

	for (int i = 0; i < 3; i++)
	{
		m_boomerangUI.push_back(Add(L"Resources/Textures/BoomerangUI.png"
			, Vector2(50 + 70 * static_cast<float>(i), 610)
			, Vector2(0.1f, 0.1f)
			, ANCHOR::MIDDLE_CENTER
			, UserInterface::Kinds::UI));
	}



	m_boomerangBackUI.push_back( Add(L"Resources/Textures/UIboomerangBack.png"
		, Vector2(50, 610)
		, Vector2(0.1f, 0.1f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI));

}

void GamePlayUI::CreateBoomerangMaker()
{
	using namespace DirectX::SimpleMath;

	m_boomerangMakerUIScale = Vector2(0.5f, 0.5f);

	m_boomerangMarkerUI =  Add(L"Resources/Textures/SlowMotionMarker.png"
		, Vector2(640, 320)
		, m_boomerangMakerUIScale
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

}
