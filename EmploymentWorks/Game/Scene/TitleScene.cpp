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
#include <cassert>

#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/Texture.h"
#include "Libraries/MyLib/Model3D.h"
#include "Libraries/MyLib/Camera/TitleCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float SELECTTEXTURESCALE = 1.0f;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TitleScene::TitleScene()
	:
	m_commonResources{},
	m_camera{},
	m_isChangeScene{},
	m_logo{},
	m_playTexture{},
	m_exitTexture{},
	m_state{},
	m_boomerangTexture{},
	m_models{}
{
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

	//auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	//auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	RECT rect{ m_commonResources->GetDeviceResources()->GetOutputSize() };

	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 1000.0f
	);

	m_camera = std::make_unique<mylib::TitleCamera>();
	m_camera->Initialize();

	m_logo = std::make_unique<mylib::Texture>();
	m_logo->Initialize(m_commonResources, L"Resources/Textures/Logo.png", DirectX::SimpleMath::Vector2(420,160), 1.0f);

	m_playTexture = std::make_unique<mylib::Texture>();
	m_playTexture->Initialize(m_commonResources, L"Resources/Textures/PLAY.png", DirectX::SimpleMath::Vector2(620, 500), SELECTTEXTURESCALE * 1.3f);

	m_exitTexture = std::make_unique<mylib::Texture>();
	m_exitTexture->Initialize(m_commonResources, L"Resources/Textures/EXIT.png", DirectX::SimpleMath::Vector2(620, 600), SELECTTEXTURESCALE);

	m_boomerangTexture = std::make_unique<mylib::Texture>();
	m_boomerangTexture->Initialize(m_commonResources, L"Resources/Textures/Boomerang.png", DirectX::SimpleMath::Vector2(100, 130), 0.4f);

	m_state = NextState::PLAY;

	//�v���C�����f���̒ǉ�
	auto model = std::make_unique<mylib::Model3D>();
	model->Initialize(m_commonResources, L"Resources/Models/NewPlayer.cmo" ,Vector3(0, 3.75f, 10),0.4f);
	model->SetRotate(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle( DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(180)));
	m_models.push_back(std::move(model));
	//�X�e�[�W���f��
	model = std::make_unique<mylib::Model3D>();
	model->Initialize(m_commonResources, L"Resources/Models/Stage.cmo", Vector3::Zero, 8.0f);
	m_models.push_back(std::move(model));
	//�G
	model = std::make_unique<mylib::Model3D>();
	model->Initialize(m_commonResources, L"Resources/Models/kariEnemy.cmo", Vector3(0, 5.75f, -10), 1.8f);
	model->SetRotate(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(90)));
	m_models.push_back(std::move(model));
	//��
	model = std::make_unique<mylib::Model3D>();
	model->Initialize(m_commonResources, L"Resources/Models/Rock.cmo", Vector3(15, 0, 0),  2.0f);
	m_models.push_back(std::move(model));
	//��
	model = std::make_unique<mylib::Model3D>();
	model->Initialize(m_commonResources, L"Resources/Models/Rock.cmo", Vector3(-15, 0, 0), 2.0f);
	m_models.push_back(std::move(model));

	// �V�[���ύX�t���O������������
	m_isChangeScene = false;




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
		m_playTexture->SetScale(SELECTTEXTURESCALE * 1.3f);
		m_exitTexture->SetScale(SELECTTEXTURESCALE);
		m_state = NextState::PLAY;
	}
	//EXIT��I��
	if (kbTracker->released.S)
	{
		m_playTexture->SetScale(SELECTTEXTURESCALE);
		m_exitTexture->SetScale(SELECTTEXTURESCALE * 1.3f);
		m_state = NextState::EXIT;

	}


	// �X�y�[�X�L�[�������ꂽ��
	if (kbTracker->released.Space)
	{
		switch (m_state)
		{
			case TitleScene::NextState::PLAY:
				m_isChangeScene = true;
				break;
			case TitleScene::NextState::EXIT:
				PostQuitMessage(0);
				break;
			default:
				break;
		}
	}

	float rotate = m_boomerangTexture->GetRotate();
	rotate += 1 * elapsedTime;

	m_camera->Update(elapsedTime);

	//m_boomerangTexture->SetRotate(rotate);

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TitleScene::Render()
{

	// �r���[�s����擾����
	const Matrix& view = m_camera->GetViewMatrix();;
	for (auto& model : m_models)
	{
		model->Render(view, m_projection);
	}




	m_boomerangTexture->Render();
	m_logo->Render();
	m_playTexture->Render();
	m_exitTexture->Render();


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
		return IScene::SceneID::PLAY;
	}

	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}


