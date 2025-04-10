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
#include "Game/Params.h"
#include "Libraries/WataLib/DetectionCollision.h"
#include "Libraries/MyLib/DebugString.h"

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
	, m_buttom{}
	, m_selectButtomId{}

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


	auto buttom = std::make_unique<UserInterface>();

	buttom->Create(m_commonResources->GetDeviceResources(), L"Resources/Textures/Tutorial.png", DirectX::SimpleMath::Vector2(400, 360), Vector2(1.3f, 1.3f));

	m_buttom[0] = std::move(buttom);

	buttom = std::make_unique<UserInterface>();

	buttom->Create(m_commonResources->GetDeviceResources(), L"Resources/Textures/Stage1.png", DirectX::SimpleMath::Vector2(880, 360), Vector2(1.3f, 1.3f));

	m_buttom[1] = std::move(buttom);

	auto texture = std::make_unique<UserInterface>();

	texture->Create(m_commonResources->GetDeviceResources(), L"Resources/Textures/BackGraund.png", Vector2(Screen::CENTER_X, Screen::CENTER_Y), Vector2(0.4f, 0.4f));

	m_textures.push_back(std::move(texture));

	m_sceneManager->SetStageID(SceneManager::Stage1);

	// �V�[���ύX�t���O������������
	m_isChangeScene = false;

	//�t�F�[�h�A�E�g�̊J�n
	m_commonResources->GetFade()->StartNormalFadeOut();

	ShowCursor(true);

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void StageSelectScene::Update(float elapsedTime)
{
	// �錾���������A���ۂ͎g�p���Ă��Ȃ��ϐ�
	UNREFERENCED_PARAMETER(elapsedTime);

	const auto& state = m_commonResources->GetInputManager()->GetMouseState();

	const auto& tracker = m_commonResources->GetInputManager()->GetMouseTracker();

	//��ʃT�C�Y�̎擾
	float widht = m_commonResources->GetDeviceResources()->GetOutputSize().right;
	float height = m_commonResources->GetDeviceResources()->GetOutputSize().bottom;



	Vector2 mousePosition = Vector2(state.x * Screen::WIDTH / widht, state.y * Screen::HEIGHT / height);


	//������
	m_selectButtomId = BUTTOM_INIAL_ID;

	for (auto& buttom : m_buttom)
	{
		buttom.second->SetScale(buttom.second->GetInialScale());
		if (WataLib::DetectionCollision::Circle_RectCheckHit(mousePosition, Params::MOUSE_RADIUS,
			buttom.second->GetPosition(), buttom.second->GetWidth(), buttom.second->GetHeight()))
		{
			buttom.second->SetScale(buttom.second->GetInialScale() * 1.4f);

			m_selectButtomId = buttom.first;

			break;

		}

	}

	//
	if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		if (m_selectButtomId != BUTTOM_INIAL_ID)
		{
			m_isChangeScene = true;

			switch (m_selectButtomId)
			{
				case 0:
					m_sceneManager->SetStageID(SceneManager::Stage1);
					break;
				case 1:
					m_sceneManager->SetStageID(SceneManager::Stage2);
					break;
				default:
					break;
			}

		}

	}

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void StageSelectScene::Render()
{
	auto states = m_commonResources->GetCommonStates();


	for (auto& texture : m_textures)
	{
		texture->Render();
	}

	for (auto& buttom : m_buttom)
	{
		buttom.second->Render();
	}

	//// �f�o�b�O����\������
	auto debugString = m_commonResources->GetDebugString();
	////debugString->AddString("Pos %f" ,m_buttom[0]->GetPosition().x);
	////debugString->AddString("Pos %f" ,m_buttom[0]->GetPosition().y);
	debugString->AddString("X %d", m_commonResources->GetDeviceResources()->GetOutputSize().right);
	debugString->AddString("Y %d", m_commonResources->GetDeviceResources()->GetOutputSize().bottom);



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
