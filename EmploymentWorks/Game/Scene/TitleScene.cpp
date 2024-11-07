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
#include "Game/Object/Wall.h"
#include "Game/Object/Rock.h"
#include "Game/Object/Ceiling.h"
#include "Game/Object/Pillar.h"
#include "Game/Object/Floor.h"
#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/Enemy.h"

#include "Game/Object/Gimmick/Artillery/Artillery.h"
#include "Libraries/MyLib/LoadJson.h"

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
	model->Initialize(m_commonResources, L"Resources/Models/Player.cmo" ,Vector3(0, 0.75f, 15),0.4f);
	model->SetRotate(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle( DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(180)));
	m_models.push_back(std::move(model));
	//�G
	model = std::make_unique<mylib::Model3D>();
	model->Initialize(m_commonResources, L"Resources/Models/BossEnemy.cmo", Vector3(0, 5.0f, 0), 1.0f);
	model->SetRotate(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0)));
	m_models.push_back(std::move(model));

	// �V�[���ύX�t���O������������
	m_isChangeScene = false;


	m_loadJson = std::make_unique<mylib::LoadJson>();

	//�X�e�[�W�̃f�[�^��ǂݍ���
	std::vector<mylib::LoadJson::Parameters> parameters = m_loadJson->GetStageDatas(L"Resources/Dates/Stage.json");


	//�X�e�[�W�I�u�W�F�b�N�Ƃ̐���
	for (auto& parameter : parameters)
	{

		//�X�e�[�W�̕�
		if (parameter.ModelName == "Stage.cmo")
		{
			auto wall = std::make_unique<Wall>();
			wall->Initialize(m_commonResources, parameter.Position, parameter.Scale, parameter.Rotation, parameter.BoundingSphereRadius);
			m_wall.push_back(std::move(wall));
		}
		else if (parameter.ModelName == "Floor.cmo")
		{
			//��	 
			m_floor = std::make_unique<Floor>();
			m_floor->Initialize(m_commonResources, parameter.Position, parameter.Scale, parameter.Rotation, parameter.BoundingSphereRadius);

		}
		else if (parameter.ModelName == "Ceiling.cmo")
		{
			//�V��
			m_ceiling = std::make_unique<Ceiling>();
			m_ceiling->Initialize(m_commonResources, parameter.Position, parameter.Scale, parameter.Rotation, parameter.BoundingSphereRadius);

		}
		else if (parameter.ModelName == "Pillar.cmo")
		{
			//��
			auto pillar = std::make_unique<Pillar>();
			pillar->Initialize(m_commonResources, parameter.Position, parameter.Scale, parameter.Rotation, parameter.BoundingSphereRadius);
			m_pillar.push_back(std::move(pillar));

		}
		else if (parameter.ModelName == "Artillery.cmo")
		{
			//�C��
			auto artillery = std::make_unique<Artillery>();
			artillery->Initialize(m_commonResources,nullptr, parameter.Position, parameter.Scale, parameter.Rotation, parameter.BoundingSphereRadius);
			m_artillery.push_back(std::move(artillery));

		}
	}



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
	const Matrix&view = m_camera->GetViewMatrix();
	

	for (auto& model : m_models)
	{
		model->Render(view, m_projection);
	}



	m_floor->Render(view, m_projection);

	for (auto& wall : m_wall)
	{
		wall->Render(view, m_projection);
	}

	for (auto& pillar : m_pillar)
	{
		pillar->Render(view, m_projection);
	}

	//m_ceiling->Render(view, m_projection);




	for (auto& artillery : m_artillery)
	{
		artillery->Render(view, m_projection);
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


