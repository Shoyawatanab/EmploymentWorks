/*
	@file	GameOverUI.cpp
	@brief	TPS�J�����N���X
*/
#include "pch.h"
#include "Game/UI/State/GameOverUI.h"
#include "Game/Screen.h"
#include "Game/Object/Player/Player.h"
#include "Libraries/MyLib/Mouse.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Game/Scene/PlayScene.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"


const int MAXANGLEY = 100;
const DirectX::SimpleMath::Vector3 TARGET = DirectX::SimpleMath::Vector3(0, 1, 0); //�X�e�[�W�̒��S

const float MOVESPEED = 0.5f;




//-------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------
GameOverUI::GameOverUI()
	
{


}

void GameOverUI::Initialize(CommonResources* resources)
{

	m_commonResources = resources;

	CreateGameOverTex();


	//�w�i�̓����x���O�ɐݒ�
	m_gameOverUI->SetAlphaValue(0.0f);
	//���g���C�摜�̓����x���O�ɐݒ�
	m_gameOverReTryUI->SetAlphaValue(-0.3f);
	//��߂�摜�̓����x���O�ɐݒ�
	m_gameOverEndUI->SetAlphaValue(-0.3f);

	m_nextState = NextState::ReTry;


}

//-------------------------------------------------------------------
// �X�V����
//-------------------------------------------------------------------
void GameOverUI::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();


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

	if (alpha < 1)
	{
		return;
	}

	if (kbTracker->released.W)
	{

		m_nextState = NextState::ReTry;
		//�傫����߂�
		m_gameOverEndUI->SetScale(m_gameOverEndUI->GetBaseScale());

	}
	else if (kbTracker->released.S)
	{

		m_nextState = NextState::End;
		m_gameOverReTryUI->SetScale(m_gameOverReTryUI->GetBaseScale());

	}

	if (kbTracker->released.Space)
	{
		switch (m_nextState)
		{
			case GameOverUI::NextState::ReTry:
				m_playScene->SetNextSceneID(PlayScene::SceneID::PLAY);
				break;
			case GameOverUI::NextState::End:
				
				PostQuitMessage(0);

				break;
			default:
				break;
		}

	}


	DirectX::SimpleMath::Vector2 scale = DirectX::SimpleMath::Vector2::Zero;


	switch (m_nextState)
	{
		case GameOverUI::NextState::ReTry:			
			scale = m_gameOverReTryUI->GetBaseScale();
			scale.x *= 1.4f;
			scale.y *= 1.4f;
			m_gameOverReTryUI->SetScale(scale);
			break;
		case GameOverUI::NextState::End:
			scale = m_gameOverEndUI->GetBaseScale();
			scale.x *= 1.4f;
			scale.y *= 1.4f;
			m_gameOverEndUI->SetScale(scale);

			break;
		default:
			break;
	}

}

void GameOverUI::Render()
{

	m_gameOverUI->Render();

	m_gameOverReTryUI->Render();

	m_gameOverEndUI->Render();




}




void GameOverUI::Enter()
{
}


void GameOverUI::Exit()
{

}

void GameOverUI::RegistrationInformation(PlayScene* playScene)
{

	m_playScene = playScene;

}


void GameOverUI::GameOverTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
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

void GameOverUI::GameOverReTryTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
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

void GameOverUI::GameOverEndTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
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

void GameOverUI::CreateGameOverTex()
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


	//��@420�@�@�@�� 510

}

