/*
	@file	StageSelectScene.cpp
	@brief	�^�C�g���V�[���N���X
*/
#include "pch.h"
#include "StageSelectScene.h"
#include "Game/Screen.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>

#include "Libraries/WataLib/Fade.h"
#include "Libraries/WataLib/DrawTexture.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
StageSelectScene::StageSelectScene(SceneManager* sceneManager)
	:
	m_commonResources{},
	m_isChangeScene{}
	,m_sceneManager{sceneManager}
	,m_tutorialUI{}
	,m_stage1UI{}
	,m_backGround{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
StageSelectScene::~StageSelectScene()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void StageSelectScene::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();


	m_tutorialUI = std::make_unique<WataLib::DrawTexture>();
	m_tutorialUI->Initialize(m_commonResources, L"Resources/Textures/Tutorial.png", DirectX::SimpleMath::Vector2(400, 360), Vector2(1.3f, 1.3f));

	m_stage1UI = std::make_unique<WataLib::DrawTexture>();

	m_stage1UI->Initialize(m_commonResources, L"Resources/Textures/Stage1.png", DirectX::SimpleMath::Vector2(880, 360), Vector2(1.3f, 1.3f));

	m_tutorialUI->SetEpansion(1.3f);

	m_backGround = std::make_unique<WataLib::DrawTexture>();
	m_backGround->Initialize(m_commonResources, L"Resources/Textures/BackGraund.png", Vector2(Screen::CENTER_X,Screen::CENTER_Y), Vector2(0.4f, 0.4f));


	auto texture = std::make_unique<WataLib::DrawTexture>();
	texture->Initialize(
		m_commonResources, L"Resources/Textures/ChangeUI2.png", DirectX::SimpleMath::Vector2(200, 650), Vector2(0.4f, 0.4f)
	);

	m_textures.push_back(std::move(texture));


	texture = std::make_unique<WataLib::DrawTexture>();
	texture->Initialize(
		m_commonResources, L"Resources/Textures/DecisionUI.png", DirectX::SimpleMath::Vector2(570, 650), Vector2(0.4f, 0.4f)
	);

	m_textures.push_back(std::move(texture));


	m_arrow = std::make_unique<WataLib::DrawTexture>();

	m_arrow->Initialize(m_commonResources, L"Resources/Textures/Arrow.png", DirectX::SimpleMath::Vector2(200, 350), Vector2(0.2f, 0.2f));




	m_sceneManager->SetStageID(SceneManager::Stage1);



	// �V�[���ύX�t���O������������
	m_isChangeScene = false;


	//�t�F�[�h�A�E�g�̊J�n
	m_commonResources->GetFade()->StartNormalFadeOut();

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void StageSelectScene::Update(float elapsedTime)
{
	// �錾���������A���ۂ͎g�p���Ă��Ȃ��ϐ�
	UNREFERENCED_PARAMETER(elapsedTime);

	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();


	if (kbTracker->released.A)
	{

		m_sceneManager->SetStageID(SceneManager::Stage1);
		m_tutorialUI->SetEpansion(1.3f);
		m_stage1UI->ResetExpansion();
		m_arrow->SetPosition(DirectX::SimpleMath::Vector2(200, 350));

	}
	else if (kbTracker->released.D)
	{
		m_sceneManager->SetStageID(SceneManager::Stage2);
		m_tutorialUI->ResetExpansion();
		m_stage1UI->SetEpansion(1.3f);
		m_arrow->SetPosition(DirectX::SimpleMath::Vector2(690, 350));

	}

	// �X�y�[�X�L�[�������ꂽ��
	if (kbTracker->pressed.Space)
	{
		m_isChangeScene = true;
	}
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void StageSelectScene::Render()
{
	auto states = m_commonResources->GetCommonStates();

	m_backGround->Render();

	m_tutorialUI->Render();

	m_stage1UI->Render();

	for (auto& texture : m_textures)
	{
		texture->Render();
	}

	m_arrow->Render();


}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void StageSelectScene::Finalize()
{
	// do nothing.
}

//---------------------------------------------------------
// ���̃V�[��ID���擾����
//---------------------------------------------------------
IScene::SceneID StageSelectScene::GetNextSceneID() const
{
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		if (m_commonResources->GetFade()->GetFadeState() == Fade::FadeState::None)
		{
			m_commonResources->GetFade()->StartNormalFadeIn();

		}

		return IScene::SceneID::PLAY;
	}

	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}
