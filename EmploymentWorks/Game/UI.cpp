/*
	@file	UI.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "UI.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Object/Enemy/Enemy.h"
#include "Game/Object/Player/Player.h"
#include "Game/Scene/PlayScene.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
UI::UI(PlayScene* playScene, Player* player, Enemy* enemy)
	:
	m_windowHeight(0)
	, m_windowWidth(0)
	, m_commonResources{}
	, m_enemy{ enemy }
	, m_player{ player }
	, m_clearUI{}
	, m_playScene{ playScene }
	, m_clearTime{}

{
	m_enemyHP.clear();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
UI::~UI()
{
	// do nothing.


}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void UI::Initialize(CommonResources* resources, int width, int height)
{
	using namespace DirectX::SimpleMath;
	assert(resources);

	m_commonResources = resources;
	m_windowWidth = width;
	m_windowHeight = height;


	CreateEnemyHP();
	CreatePlayerHP();
	CreateClearTex();
	CreateGameOverTex();

	//�{�XHP�̊������Z�b�g����
	float EnemyHp = m_enemy->GetHp();
	float ratio = EnemyHp / m_enemy->GetMAXHp();
	m_enemyHP[1]->SetRenderRatio(ratio);

	//�w�i�̓����x���O�ɐݒ�
	m_gameOverUI->SetAlphaValue(0.0f);
	//���g���C�摜�̓����x���O�ɐݒ�
	m_gameOverReTryUI->SetAlphaValue(-0.3f);
	//��߂�摜�̓����x���O�ɐݒ�
	m_gameOverEndUI->SetAlphaValue(-0.3f);
	//���摜�̓����x�̐ݒ�
	m_gameOverArrowUI->SetAlphaValue(-0.3f);

	m_clearTime = 0;

	m_changeResultScene = false;


}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void UI::Update(float elapsedTime)
{

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	UNREFERENCED_PARAMETER(elapsedTime);

	float EnemyHp = m_enemy->GetHp();


	float ratio = EnemyHp / m_enemy->GetMAXHp();

	//ratio = 0.5f;

	m_enemyHP[1]->SetRenderRatio(ratio);


}

void UI::GameClearUpdate(float elapsedTime)
{

	DirectX::SimpleMath::Vector2 pos = m_clearUI->GetPosition();

	pos.y += 200.0f * elapsedTime;

	pos.y = std::min(pos.y, 360.0f);

	m_clearUI->SetPosition(pos);

	if (pos.y <= 360)
	{

		//�N���A�̉摜�����S�ɗ��Ă���̎��Ԃ̌v��
		m_clearTime += elapsedTime;

	}

	if (m_clearTime >= 3)
	{
		m_changeResultScene = true;
	}

}


void UI::GameOverUpdate(float elapsedTime)
{




	//���Z�l�����߂�
	float Additive = 0.5f * elapsedTime;



	//�w�i�̓����x�̕ύX
	float alpha;
	alpha = m_gameOverUI->GetAlphaValue();
	//�����x�����Z
	alpha += Additive;
	//�����x���Z�b�g
	m_gameOverUI->SetAlphaValue(alpha);


	//���g���C�摜�̓����x�̎擾
	alpha = m_gameOverReTryUI->GetAlphaValue();
	//�����x�����Z
	alpha += Additive;
	//�����x���Z�b�g
	m_gameOverReTryUI->SetAlphaValue(alpha);


	//��߂�摜�̓����x�̎擾
	alpha = m_gameOverEndUI->GetAlphaValue();
	//�����x�����Z
	alpha += Additive;
	//�����x���Z�b�g
	m_gameOverEndUI->SetAlphaValue(alpha);

	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	if (kbTracker->released.W)
	{

		m_gameOverArrowUI->SetPosition(DirectX::SimpleMath::Vector2(500, 420));

	}
	else if (kbTracker->released.S)
	{

		m_gameOverArrowUI->SetPosition(DirectX::SimpleMath::Vector2(500, 510));


	}

	if (kbTracker->released.Space)
	{

		//���g���C�Ȃ�
		if (m_gameOverArrowUI->GetPosition().y <= 420)
		{

			m_playScene->SetNextSceneID(PlayScene::SceneID::PLAY);

		}
		else
		{
			//��߂�
			PostQuitMessage(0);
		}

	}

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void UI::Render()
{
	using namespace DirectX::SimpleMath;

	for (auto& enemyHP : m_enemyHP)
	{
		enemyHP->Render();

	}



	for (int i = 0; i < m_player->GetPlayerHP(); i++)
	{
		m_playerHP[i]->Render();

	}




}

/// <summary>
/// �N���A��Q�[���I�[�o�[�̃e�L�X�g�\���֐�
/// </summary>
void UI::ClearTexRender()
{

	m_clearUI->Render();

}

void UI::GameOverRender()
{

	m_gameOverUI->Render();

	m_gameOverReTryUI->Render();

	m_gameOverEndUI->Render();

	m_gameOverArrowUI->Render();


}



void UI::EnemyHPAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
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

	m_enemyHP.push_back(std::move(userInterface));

}

void UI::PlayerHPAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
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

	m_playerHP.push_back(std::move(userInterface));

}

/// <summary>
/// Claer�摜�̒ǉ�
/// </summary>
/// <param name="path"></param>
/// <param name="position"></param>
/// <param name="scale"></param>
/// <param name="anchor"></param>
/// <param name="kind"></param>
void UI::ClearTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
{

	m_clearUI = std::make_unique<UserInterface>();
	//  �w�肳�ꂽ�摜��\�����邽�߂̃A�C�e�����쐬����
	m_clearUI->Create(m_commonResources->GetDeviceResources()
		, path
		, position
		, scale
		, anchor
		, kind);

	m_clearUI->SetWindowSize(m_windowWidth, m_windowHeight);


}

void UI::GameOverTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
{

	m_gameOverUI = std::make_unique<UserInterface>();
	//  �w�肳�ꂽ�摜��\�����邽�߂̃A�C�e�����쐬����
	m_gameOverUI->Create(m_commonResources->GetDeviceResources()
		, path
		, position
		, scale
		, anchor
		, kind);

	m_gameOverUI->SetWindowSize(m_windowWidth, m_windowHeight);


}

void UI::GameOverReTryTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
{

	m_gameOverReTryUI = std::make_unique<UserInterface>();
	//  �w�肳�ꂽ�摜��\�����邽�߂̃A�C�e�����쐬����
	m_gameOverReTryUI->Create(m_commonResources->GetDeviceResources()
		, path
		, position
		, scale
		, anchor
		, kind);

	m_gameOverReTryUI->SetWindowSize(m_windowWidth, m_windowHeight);


}

void UI::GameOverEndTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
{

	m_gameOverEndUI = std::make_unique<UserInterface>();
	//  �w�肳�ꂽ�摜��\�����邽�߂̃A�C�e�����쐬����
	m_gameOverEndUI->Create(m_commonResources->GetDeviceResources()
		, path
		, position
		, scale
		, anchor
		, kind);

	m_gameOverEndUI->SetWindowSize(m_windowWidth, m_windowHeight);


}

void UI::GameOverArrowTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
{

	m_gameOverArrowUI = std::make_unique<UserInterface>();
	//  �w�肳�ꂽ�摜��\�����邽�߂̃A�C�e�����쐬����
	m_gameOverArrowUI->Create(m_commonResources->GetDeviceResources()
		, path
		, position
		, scale
		, anchor
		, kind);

	m_gameOverArrowUI->SetWindowSize(m_windowWidth, m_windowHeight);


}

void UI::CreateEnemyHP()
{
	using namespace DirectX::SimpleMath;
	//  �w�i�ƂȂ�E�B���h�E�摜��ǂݍ���

	EnemyHPAdd(L"Resources/Textures/BossHPBase.png"
		, Vector2(640, 50)
		, Vector2(0.9f, 0.5f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

	EnemyHPAdd(L"Resources/Textures/EnemyHP.png"
		, Vector2(640, 50)
		, Vector2(0.91f, 0.39f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

	EnemyHPAdd(L"Resources/Textures/EnemyName.png"
		, Vector2(640, 25)
		, Vector2(0.3f, 0.3f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);


}

void UI::CreatePlayerHP()
{
	using namespace DirectX::SimpleMath;

	for (int i = 0; i < 3; i++)
	{
		//  ���摜��ǂݍ���
		PlayerHPAdd(L"Resources/Textures/HP.png"
			, Vector2(50 + 70 * i, 680)
			, Vector2(1.0f, 1.0f)
			, ANCHOR::MIDDLE_CENTER
			, UserInterface::Kinds::UI);

	}


}

void UI::CreateClearTex()
{
	using namespace DirectX::SimpleMath;

	ClearTexAdd(L"Resources/Textures/GameClear.png"
		, Vector2(640, -50)
		, Vector2(0.5f, 0.5f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

}

void UI::CreateGameOverTex()
{

	using namespace DirectX::SimpleMath;

	GameOverTexAdd(L"Resources/Textures/GameOver.png"
		, Vector2(640, 360)
		, Vector2(1.0f, 1.0f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

	GameOverReTryTexAdd(L"Resources/Textures/ReTry.png"
		, Vector2(640, 420)
		, Vector2(0.3f, 0.3f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

	GameOverEndTexAdd(L"Resources/Textures/End.png"
		, Vector2(640, 510)
		, Vector2(0.3f, 0.3f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

	GameOverArrowTexAdd(L"Resources/Textures/Arrow.png"
		, Vector2(500, 420)
		, Vector2(0.18f, 0.18f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

	//��@420�@�@�@�� 510

}

