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
#include "Game/Params.h"
#include "Libraries/WataLib/DetectionCollision.h"


#include "Libraries/MyLib/DebugString.h"

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
	,m_state{State::PLAY}
	,m_buttom{}
	,m_selectButtomId{}
	,m_player{}
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

	//auto model = std::make_unique<WataLib::Model3D>();
	//model->Initialize(m_commonResources, L"Resources/Models/Player.cmo",
	//	PLAYERPOSITION, PLAYERSCALE);

	//m_objects.push_back(std::move(model));

	m_player = std::make_unique<Player>(m_commonResources);
	m_player->AddPointer(nullptr,nullptr);

	m_player->Initialize();

	m_player->SetPosition(PLAYERPOSITION);
	m_player->SetScale(PLAYERSCALE);
	m_player->SetRotation(DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(PLAYERROTATION.y),
		DirectX::XMConvertToRadians(PLAYERROTATION.x),
		DirectX::XMConvertToRadians(PLAYERROTATION.z)));

	CreateTextures();

	// �V�[���ύX�t���O������������
	m_isChangeScene = false;

	//�t�F�[�h�A�E�g�̊J�n
	m_commonResources->GetFade()->StartNormalFadeOut();

	ShowCursor(true);



}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TitleScene::Update(float elapsedTime)
{
	// �錾���������A���ۂ͎g�p���Ă��Ȃ��ϐ�
	UNREFERENCED_PARAMETER(elapsedTime);


	const auto& state = m_commonResources->GetInputManager()->GetMouseState();

	const auto& tracker = m_commonResources->GetInputManager()->GetMouseTracker();

	RECT rect{ m_commonResources->GetDeviceResources()->GetOutputSize() };

	//��ʃT�C�Y�̎擾
	float widht = static_cast<float>(m_commonResources->GetDeviceResources()->GetOutputSize().right);
	float height = static_cast<float>(m_commonResources->GetDeviceResources()->GetOutputSize().bottom);

	Vector2 mousePosition = Vector2(state.x * Screen::WIDTH / widht, state.y * Screen::HEIGHT / height) ;
	//Vector2 mousePosition = Vector2(state.x , state.y) ;
	
	//������
	m_selectButtomId = BUTTOM_INIAL_ID;
	
	for (auto& buttom : m_buttom)
	{
		buttom.second->SetScale(buttom.second->GetInialScale());

		if (WataLib::DetectionCollision::Circle_RectCheckHit(Vector2(mousePosition.x,mousePosition.y), Params::MOUSE_RADIUS,
			buttom.second->GetPosition(), static_cast<float>(buttom.second->GetWidth()), static_cast<float>(buttom.second->GetHeight())))
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

			switch (m_selectButtomId)
			{
				case 0:
					m_isChangeScene = true;
					break;
				case 1:
					PostQuitMessage(0);
					break;
				default:
					break;
			}
		}
	}


	m_camera->Update(elapsedTime);

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TitleScene::Render()
{

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

	m_player->Render(view, m_projection);


	for (auto& texture : m_textures)
	{
		texture->Render();
	}

	for (auto& buttom : m_buttom)
	{
		buttom.second->Render();
	}



	////// �f�o�b�O����\������
	//auto debugString = m_commonResources->GetDebugString();
	//////debugString->AddString("Pos %f" ,m_buttom[0]->GetPosition().x);
	//////debugString->AddString("Pos %f" ,m_buttom[0]->GetPosition().y);
	//debugString->AddString("X %d" , m_commonResources->GetDeviceResources()->GetOutputSize().right);
	//debugString->AddString("Y %d" , m_commonResources->GetDeviceResources()->GetOutputSize().bottom);


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
		if (m_commonResources->GetFade()->GetFadeState() == Fade::FadeState::NONE)
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

	auto texture = std::make_unique<UserInterface>();
	//texture->Create(
	//	m_commonResources->GetDeviceResources(), L"Resources/Textures/Logo.png", DirectX::SimpleMath::Vector2(420, 120), Vector2(0.25f, 0.25f)
	//);
	texture->Create(
		m_commonResources, "Logo", DirectX::SimpleMath::Vector2(420, 120), Vector2(0.25f, 0.25f)
	);

	m_textures.push_back(std::move(texture));


	auto buttom = std::make_unique<UserInterface>();
	//buttom->Initialize(m_commonResources, L"Resources/Textures/PLAY.png", DirectX::SimpleMath::Vector2(1000, 500), Vector2(1.1f, 1.1f));

	buttom->Create(m_commonResources, "PLAY", DirectX::SimpleMath::Vector2(1000, 500), Vector2(1.1f, 1.1f));


		
	m_buttom[0] = std::move(buttom);

	buttom = std::make_unique<UserInterface>();
	//buttom->Initialize(m_commonResources, L"Resources/Textures/EXIT.png", DirectX::SimpleMath::Vector2(1000, 630), Vector2(1.2f, 1.2f));

	buttom->Create(m_commonResources, "EXIT", DirectX::SimpleMath::Vector2(1000, 630), Vector2(1.2f, 1.2f));

	m_buttom[1] = std::move(buttom);


}
