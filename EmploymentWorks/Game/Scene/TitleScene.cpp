/*
	@file	TitleScene.cpp
	@brief	�^�C�g���V�[���N���X
*/
#include "pch.h"
#include "TitleScene.h"
#include "Game/Screen.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/WataLib/Fade.h"
#include <cassert>
#include "Libraries/WataLib/Json.h"
#include "Game/StageObject/Floor.h"
#include "Game/StageObject/Wall.h"
#include "Libraries/WataLib/Camera/TitleCamera.h"
#include "Libraries/WataLib/Model3D.h"
#include "Libraries/WataLib/DrawTexture.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TitleScene::TitleScene()
	:
	m_commonResources{},
	m_projection{},
	m_isChangeScene{}
	,m_object{}
	,m_camera{}
	,m_textures{}
	,m_playUI{}
	,m_exitUI{}
	,m_state{State::PLAY}
{

	m_camera = std::make_unique<WataLib::TitleCamera>();

}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
TitleScene::~TitleScene()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void TitleScene::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

	RECT rect{ m_commonResources->GetDeviceResources()->GetOutputSize() };

	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 1000.0f
	);

	m_camera->Initialize(m_commonResources);


	std::vector<WataLib::Json::StageData> stageParameters;

	std::unique_ptr<WataLib::Json> json = std::make_unique<WataLib::Json>();


	stageParameters = json->LoadStageDatas(L"Stage");

	//�X�e�[�W�I�u�W�F�b�N�Ƃ̐���
	for (auto& parameter : stageParameters)
	{

		if (parameter.ModelName == "Floor")
		{

			auto floor = std::make_unique<Floor>(
				m_commonResources,
				parameter.Scale, parameter.Position,
				Quaternion::CreateFromYawPitchRoll(
					DirectX::XMConvertToRadians(parameter.Rotation.y),
					DirectX::XMConvertToRadians(parameter.Rotation.x),
					DirectX::XMConvertToRadians(parameter.Rotation.z)));

			floor->Initialize();

			m_object.push_back(std::move(floor));

		}
		else if (parameter.ModelName == "Wall")
		{


			auto wall = std::make_unique<Wall>(
				m_commonResources,
				parameter.Scale, parameter.Position,
				Quaternion::CreateFromYawPitchRoll(
					DirectX::XMConvertToRadians(parameter.Rotation.y),
					DirectX::XMConvertToRadians(parameter.Rotation.x),
					DirectX::XMConvertToRadians(parameter.Rotation.z)));

			wall->Initialize();
			m_object.push_back(std::move(wall));
		}

	}

	auto model = std::make_unique<WataLib::Model3D>();
	model->Initialize(m_commonResources, L"Resources/Models/Player.cmo",
		PLAYERPOSITION, PLAYERSCALE);

	m_objects.push_back(std::move(model));


	CreateTextures();

	// �V�[���ύX�t���O������������
	m_isChangeScene = false;

	ShowCursor(FALSE);
	m_playUI->SetEpansion(EXPANSION);

	//�t�F�[�h�A�E�g�̊J�n
	m_commonResources->GetFade()->StartNormalFadeOut();


}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TitleScene::Update(float elapsedTime)
{
	// �錾���������A���ۂ͎g�p���Ă��Ȃ��ϐ�
	UNREFERENCED_PARAMETER(elapsedTime);

	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();


	//PLAY��I��
	if (kbTracker->released.W)
	{
		m_state = State::PLAY;
		m_exitUI->ResetExpansion();
		m_playUI->SetEpansion(EXPANSION);
	}
	//EXIT��I��
	if (kbTracker->released.S)
	{
		m_state = State::EXIT;
		m_exitUI->SetEpansion(EXPANSION);
		m_playUI->ResetExpansion();
	}

	// �X�y�[�X�L�[�������ꂽ��
	if (kbTracker->pressed.Space)
	{
		switch (m_state)
		{
			case TitleScene::State::PLAY:				
				m_isChangeScene = true;
				break;
			case TitleScene::State::EXIT:
				PostQuitMessage(0);
				break;
			default:
				break;
		}
	}

	m_camera->Update(elapsedTime);

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TitleScene::Render()
{
	auto states = m_commonResources->GetCommonStates();


	// �r���[�s����擾����
	const Matrix& view = m_camera->GetViewMatrix();


	for (auto& object : m_object)
	{
		object->Render(view, m_projection);
	}

	for (auto& object : m_objects)
	{
		object->Render(view, m_projection);
	}

	for (auto& texture : m_textures)
	{
		texture->Render();
	}

	m_playUI->Render();
	m_exitUI->Render();
	m_arrow->Render();

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void TitleScene::Finalize()
{
	// do nothing.
}

//---------------------------------------------------------
// ���̃V�[��ID���擾����
//---------------------------------------------------------
IScene::SceneID TitleScene::GetNextSceneID() const
{
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		//�t�F�[�h���łȂ��Ȃ�
		if (m_commonResources->GetFade()->GetFadeState() == Fade::FadeState::None)
		{
			//�t�F�[�h�C�����J�n
			m_commonResources->GetFade()->StartNormalFadeIn();

		}


		return IScene::SceneID::STAGESELECT;
	}

	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}

void TitleScene::CreateTextures()
{

	auto texture = std::make_unique<WataLib::DrawTexture>();
	texture->Initialize(
		m_commonResources, L"Resources/Textures/Logo.png", DirectX::SimpleMath::Vector2(420, 120), Vector2(0.25f, 0.25f)
	);

	m_textures.push_back(std::move(texture));

	texture = std::make_unique<WataLib::DrawTexture>();
	texture->Initialize(
		m_commonResources, L"Resources/Textures/Boomerang.png", DirectX::SimpleMath::Vector2(100, 130), Vector2(0.4f, 0.4f)
	);


	texture = std::make_unique<WataLib::DrawTexture>();
	texture->Initialize(
		m_commonResources, L"Resources/Textures/ChangeUI.png", DirectX::SimpleMath::Vector2(200, 650), Vector2(0.4f, 0.4f)
	);

	m_textures.push_back(std::move(texture));


	texture = std::make_unique<WataLib::DrawTexture>();
	texture->Initialize(
		m_commonResources, L"Resources/Textures/DecisionUI.png", DirectX::SimpleMath::Vector2(570, 650), Vector2(0.4f, 0.4f)
	);

	m_textures.push_back(std::move(texture));


	m_playUI = std::make_unique<WataLib::DrawTexture>();
	m_playUI->Initialize(m_commonResources, L"Resources/Textures/PLAY.png", DirectX::SimpleMath::Vector2(1000, 500), Vector2(1.1f, 1.1f));

	m_exitUI = std::make_unique<WataLib::DrawTexture>();

	m_exitUI->Initialize(m_commonResources, L"Resources/Textures/EXIT.png", DirectX::SimpleMath::Vector2(1000, 630), Vector2(1.2f, 1.2f));


	m_arrow = std::make_unique<WataLib::DrawTexture>();

	m_arrow->Initialize(m_commonResources, L"Resources/Textures/Arrow.png", DirectX::SimpleMath::Vector2(800, 500), Vector2(0.2f, 0.2f));


}
