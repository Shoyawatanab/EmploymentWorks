/*
	@file	GameClearUI.cpp
	@brief	TPS�J�����N���X
*/
#include "pch.h"
#include "Game/UI/State//GameClearUI.h"
#include "Game/Screen.h"
#include "Game/Object/Player/Player.h"
#include "Libraries/MyLib/Mouse.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Scene/PlayScene.h"

const int MAXANGLEY = 100;
const DirectX::SimpleMath::Vector3 TARGET = DirectX::SimpleMath::Vector3(0, 1, 0); //�X�e�[�W�̒��S

const float MOVESPEED = 0.5f;




//-------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------
GameClearUI::GameClearUI()
	:
	m_commonResources{},
	m_clearTime{}
{


}

void GameClearUI::Initialize(CommonResources* resources)
{
	m_commonResources = resources;


	CreateClearTex();

	m_clearTime = 0;

	m_changeResultScene = false;

	m_nextState = NextState::ReTry;

	m_lerpTime = 0;

}

//-------------------------------------------------------------------
// �X�V����
//-------------------------------------------------------------------
void GameClearUI::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//float additive = 1.7f * elapsedTime;

	//�w�i��傫������
	//DirectX::SimpleMath::Vector2 scale = m_clearUI->GetScale();

	//scale.x += additive;
	//scale.y += additive;

	//scale.x = std::min(scale.x,1.0f);
	//scale.y = std::min(scale.y, 1.0f);

	//m_clearUI->SetScale(scale);

	//scale = m_reTryUI->GetScale();

	//scale.x += additive;
	//scale.y += additive;

	//scale.x = std::min(scale.x, 1.0f);
	//scale.y = std::min(scale.y, 1.0f);

	//m_reTryUI->SetScale(scale);

	//scale = m_titleUI->GetScale();

	//scale.x += additive;
	//scale.y += additive;

	//scale.x = std::min(scale.x, 1.0f);
	//scale.y = std::min(scale.y, 1.0f);

	//m_titleUI->SetScale(scale);

	DirectX::SimpleMath::Vector2 Position;
	DirectX::SimpleMath::Vector2 Scale;


	//�w�i�̍��W
	Position = DirectX::SimpleMath::Vector2::Lerp(m_clearUI->GetStartPosition(),m_clearUI->GetEndPosition(),m_lerpTime);
	//�w�i�̑傫��
	Scale = DirectX::SimpleMath::Vector2::Lerp(m_clearUI->GetStartScale(), m_clearUI->GetEndScale(), m_lerpTime);
	//�l�̑��
	m_clearUI->SetPosition(Position);
	m_clearUI->SetScale(Scale);

	//ReTry�摜�̍��W
	Position = DirectX::SimpleMath::Vector2::Lerp(m_reTryUI->GetStartPosition(), m_reTryUI->GetEndPosition(), m_lerpTime);
	//ReTry�摜�̑傫��
	Scale = DirectX::SimpleMath::Vector2::Lerp(m_reTryUI->GetStartScale(), m_reTryUI->GetEndScale(), m_lerpTime);
	//�l�̑��
	m_reTryUI->SetPosition(Position);
	m_reTryUI->SetScale(Scale);

	//Title�摜�̍��W
	Position = DirectX::SimpleMath::Vector2::Lerp(m_titleUI->GetStartPosition(), m_titleUI->GetEndPosition(), m_lerpTime);
	//title�摜�̑傫��
	Scale = DirectX::SimpleMath::Vector2::Lerp(m_titleUI->GetStartScale(), m_titleUI->GetEndScale(), m_lerpTime);
	//�l�̑��
	m_titleUI->SetPosition(Position);
	m_titleUI->SetScale(Scale);


	m_lerpTime += elapsedTime;


	m_lerpTime = std::min(m_lerpTime, 1.0f);


	if (m_lerpTime < 1)
	{
		return;
	}

	//�w�i���ő�܂ő傫���Ȃ�����

	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	if (kbTracker->released.W)
	{
		m_nextState = NextState::ReTry;
		//�傫����߂�
		//m_titleUI->SetScale(m_titleUI->GetBaseScale());
	}
	else if (kbTracker->released.S)
	{
		m_nextState = NextState::Title;
		//�傫����߂�
		//m_reTryUI->SetScale(m_reTryUI->GetBaseScale());

	}

	if (kbTracker->released.Space)
	{
		switch (m_nextState)
		{
			case GameClearUI::NextState::ReTry:				
				m_playScene->SetNextSceneID(PlayScene::SceneID::PLAY);
				break;
			case GameClearUI::NextState::Title:
				m_playScene->SetNextSceneID(PlayScene::SceneID::TITLE);

				break;
			default:
				break;
		}
	}


	
	//�I�΂�Ă���摜�̑傫���������傫������
	switch (m_nextState)
	{
		case GameClearUI::NextState::ReTry:
			Scale = m_reTryUI->GetScale();
			Scale.x *= 1.3f;
			Scale.y *= 1.3f;

			m_reTryUI->SetScale(Scale);

			break;
		case GameClearUI::NextState::Title:
			Scale = m_titleUI->GetScale();
			Scale.x *= 1.3f;
			Scale.y *= 1.3f;

			m_titleUI->SetScale(Scale);

			break;
		default:
			break;
	}

}

void GameClearUI::Render()
{

	m_clearUI->Render();

	m_reTryUI->Render();

	m_titleUI->Render();

}




void GameClearUI::Enter()
{

	m_lerpTime = 0;

}


void GameClearUI::Exit()
{

}

void GameClearUI::RegistrationInformation(PlayScene* playScene)
{

	m_playScene = playScene;

}

/// <summary>
/// Claer�摜�̒ǉ�
/// </summary>
/// <param name="path"></param>
/// <param name="position"></param>
/// <param name="scale"></param>
/// <param name="anchor"></param>
/// <param name="kind"></param>
void GameClearUI::ClearTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
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

	//�I�����̍��W�̐ݒ�
	m_clearUI->SetEndPosition(DirectX::SimpleMath::Vector2(640,360));
	//�I�����̑傫���̐ݒ�
	m_clearUI->SetEndScale(DirectX::SimpleMath::Vector2::One);

}

void GameClearUI::ReTryTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
{

	m_reTryUI = std::make_unique<UserInterface>();
	//  �w�肳�ꂽ�摜��\�����邽�߂̃A�C�e�����쐬����
	m_reTryUI->Create(m_commonResources->GetDeviceResources()
		, path
		, position
		, scale
		, anchor
		, kind);

	m_reTryUI->SetWindowSize(m_windowWidth, m_windowHeight);

	//�I�����̍��W�̐ݒ�
	m_reTryUI->SetEndPosition(DirectX::SimpleMath::Vector2(640, 370));
	//�I�����̑傫���̐ݒ�
	m_reTryUI->SetEndScale(DirectX::SimpleMath::Vector2::One);

}

void GameClearUI::TitleTexAdd(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor, UserInterface::Kinds kind)
{

	m_titleUI = std::make_unique<UserInterface>();
	//  �w�肳�ꂽ�摜��\�����邽�߂̃A�C�e�����쐬����
	m_titleUI->Create(m_commonResources->GetDeviceResources()
		, path
		, position
		, scale
		, anchor
		, kind);

	m_titleUI->SetWindowSize(m_windowWidth, m_windowHeight);
	//�I�����̍��W�̐ݒ�
	m_titleUI->SetEndPosition(DirectX::SimpleMath::Vector2(640, 500));
	//�I�����̑傫���̐ݒ�
	m_titleUI->SetEndScale(DirectX::SimpleMath::Vector2::One);

}



void GameClearUI::CreateClearTex()
{
	using namespace DirectX::SimpleMath;

	ClearTexAdd(L"Resources/Textures/ClearBackGraund.png"
		, Vector2(640, 360)
		, Vector2(0.0f, 0.0f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

	ReTryTexAdd(L"Resources/Textures/ClearReTryTex.png"
		, Vector2(640, 360)
		, Vector2(0.0f, 0.0f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);

	TitleTexAdd(L"Resources/Textures/ClearTitleTex.png"
		, Vector2(640, 360)
		, Vector2(0.0f,0.0f)
		, ANCHOR::MIDDLE_CENTER
		, UserInterface::Kinds::UI);


}



