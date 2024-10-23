/*
	@file	PlayScene.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "PlayScene.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"

#include "Libraries/MyLib/Camera/GameCameraManager.h"
#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/Enemy.h"
#include "Game/Object/Floor.h"
#include "Game/LockOn.h"
#include "Game/DetectionCollision/CollisionManager.h"
#include "Game/Object/Wall.h"
#include "Game/EnemyHP.h"
#include "Game/Object/Rock.h"
#include "Game/Object/Sky.h"
#include "Game/UI/UI.h"
#include "Game/Object/Ceiling.h"
#include "Game/Object/Pillar.h"
#include "Game/Object/Gimmick/Artillery/Artillery.h"
#include "Libraries/MyLib/LoadJson.h"

#include <cassert>

const int WALLSIZE = 4;
const float WALLHEITH = 2;


//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayScene::PlayScene()
	:
	m_commonResources{},
	//m_debugCamera{},
	m_gridFloor{},
	m_projection{},
	m_player{},
	m_enemy{},
	m_cameraManager{},
	m_floor{}
	, m_lockOn{}
	, m_rock{}
	, m_sky{}
	, m_nextScene{ SceneID::NONE }
	,m_state{}
	,m_ceiling{}
	,m_loadJson{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayScene::~PlayScene()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayScene::Initialize(CommonResources* resources)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	assert(resources);
	m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	m_nextScene = SceneID::NONE;

	// �O���b�h�����쐬����
	m_gridFloor = std::make_unique<mylib::GridFloor>(device, context, states);

	// �f�o�b�O�J�������쐬����
	RECT rect{ m_commonResources->GetDeviceResources()->GetOutputSize() };
	//m_debugCamera = std::make_unique<mylib::DebugCamera>();
	//m_debugCamera->Initialize(rect.right, rect.bottom);



	// �ˉe�s����쐬����
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 1000.0f
	);

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
		else if(parameter.ModelName == "Floor.cmo")
		{
			//��	 
			m_floor = std::make_unique<Floor>();
			m_floor->Initialize(m_commonResources, parameter.Position, parameter.Scale, parameter.Rotation,parameter.BoundingSphereRadius);

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
			artillery->Initialize(m_commonResources, parameter.Position, parameter.Scale, parameter.Rotation, parameter.BoundingSphereRadius);
			m_artillery.push_back(std::move(artillery));

		}
	}


	DirectX::SimpleMath::Quaternion rotation = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0), 0, DirectX::XMConvertToRadians(0));

	float scale = 1.0f;


	m_enemy = std::make_unique<Enemy>(m_commonResources,nullptr,  DirectX::SimpleMath::Vector3(scale, scale, scale), Vector3(0, 5, 0), rotation);
	m_player = std::make_unique<Player>();
	m_cameraManager = std::make_unique<mylib::GameCameraManager>();



	m_lockOn = std::make_unique<LockOn>();
	m_collisionManager = std::make_unique<CollisionManager>();
	m_ui = std::make_unique<UI>();

	//�e�N���X�ɕK�v�ȃN���X�̃C���X�^���X
	m_player->Instances();
	m_enemy->Instances();
	m_cameraManager->Instances();
	m_ui->Instances();



	//�e�N���X�̏���o�^�ƃC���X�^���X
	m_player->RegistrationInformation(m_enemy.get(),m_cameraManager->GetTPSCamera());
	m_enemy->RegistrationInformation(m_player.get());
	m_cameraManager->RegistrationInformation(this, m_player.get(), m_enemy.get());
	m_lockOn->RegistrationInformation(m_player.get(), m_enemy.get(), m_cameraManager.get());
	m_ui->RegistrationInformation(this, m_player.get(), m_enemy.get());


	Vector3 floorScale = Vector3(70, 0.1f, 50);


	m_player->Initialize(m_commonResources, Vector3(0, 3.75f, 15));
	m_enemy->Initialize();


	
	m_cameraManager->Initialize();
	m_lockOn->Initialize(m_commonResources->GetDeviceResources(),
		m_commonResources->GetDeviceResources()->GetOutputSize().right,
		m_commonResources->GetDeviceResources()->GetOutputSize().bottom);
	m_collisionManager->Initialize(m_commonResources, m_player.get(), m_enemy.get());
	m_ui->Initialize(m_commonResources,
		m_commonResources->GetDeviceResources()->GetOutputSize().right,
		m_commonResources->GetDeviceResources()->GetOutputSize().bottom);

	m_collisionManager->SetTPS_Camera(m_cameraManager->GetTPSCamera());


	///�����蔻���Manager�ɒǉ�
	m_player->RegistrationCollionManager(m_collisionManager.get());
	m_enemy->RegistrationCollionManager(m_collisionManager.get());
	m_floor->RegistrationCollionManager(m_collisionManager.get());

	for (auto& wall : m_wall)
	{
		wall->RegistrationCollionManager(m_collisionManager.get());
	}

	for (auto& artillery : m_artillery)
	{
		artillery->RegistrationCollionManager(m_collisionManager.get());
	}

	for (auto& pillar : m_pillar)
	{
		pillar->RegistrationCollionManager(m_collisionManager.get());
	}

	//m_rock[0]->RegistrationCollionManager(m_collisionManager.get());
	//m_rock[1]->RegistrationCollionManager(m_collisionManager.get());


	//Ray�Ƃ̓����蔻�����邽�߂�Bounding�̓o�^
	//m_commonResources->GetJudgement()->SetBounding(m_rock[0]->GetBounding());
	//m_commonResources->GetJudgement()->SetBounding(m_rock[1]->GetBounding());


	m_sky = std::make_unique<Sky>();
	m_sky->Initialize(m_commonResources);

	m_state = GameState::None;

	Vector3 pos = m_enemy->GetBeamStartPosition();

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	m_cameraManager->Update(elapsedTime);

	switch (m_state)
	{
		case PlayScene::GameState::None:


			if (m_cameraManager->GetGameCameraState() != m_cameraManager->GetGameStartCamera())
			{
				m_enemy->Update(elapsedTime);
				for (auto& artillery : m_artillery)
				{
					artillery->Update(elapsedTime);
				}
			}


			//�Q�[���N���A���ɂP�x�����Ăт���
			if (m_enemy->GetHp() <= 0)
			{
				//�J�����̐؂�ւ�
				m_cameraManager->ChangeState(m_cameraManager->GetGameEndCamera());
				//�Q�[����Ԃ��N���A�ɕύX
				m_state = GameState::Clear;
				m_enemy->SetAnimation("FallDown");

			}

			//�Q�[���I�[�o�[�ɕύX
			if (m_player->GetPlayerHP() <= 0)
			{
				m_state = GameState::GameOver;
			}

			m_lockOn->Update(elapsedTime);



			m_commonResources->GetTimer()->Update(elapsedTime);


			break;
		case PlayScene::GameState::Clear:

			//TPS�J�����ɂȂ��ăQ�[�����ʏ��Ԃ̎�
			if (m_cameraManager->GetGameCameraState() != m_cameraManager->GetGameStartCamera())
			{
				
				if (m_enemy->FallDwonAnimation(elapsedTime) == BossEnemyBase::AnimationStage::Success && m_ui->GetCurrentUIState() != m_ui->GetGameClearUI())
				{
					m_ui->ChangeState(m_ui->GetGameClearUI());

				}
			
			}

			////�G��|�����Ƃ��̃A�j���[�V�������I�������
			if (m_enemy->GetScale().x <= 0 && m_ui->GetCurrentUIState() != m_ui->GetGameClearUI())
			{
			}

			break;
		case PlayScene::GameState::GameOver:

			if (m_ui->GetCurrentUIState() != m_ui->GetGameOverUI())
			{
				m_ui->ChangeState(m_ui->GetGameOverUI());
			}

			break;
		default:
			break;
	}



	m_player->Update(elapsedTime);

	m_ui->Update(elapsedTime);

	m_collisionManager->Update();



	m_player->SetisLockOn(m_lockOn->GetIsLOckOn());

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayScene::Render()
{
	using namespace DirectX::SimpleMath;


	// �r���[�s����擾����
	const Matrix& view = m_cameraManager->GetViewMatrix();;


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

	m_enemy->Render(view, m_projection);


	m_sky->Render(view, m_projection);

	for (auto& artillery : m_artillery)
	{
		artillery->Render(view, m_projection);
	}


	if (m_state == GameState::None)
	{
		m_player->Render(view, m_projection);
		m_lockOn->Render();
	}

	m_ui->Render();

	m_commonResources->GetTimer()->PlaySceneRender(Vector2(100, 50), 0.3f);

	//// �f�o�b�O�����uDebugString�v�ŕ\������
	auto debugString = m_commonResources->GetDebugString();
	//debugString->AddString("Play Scene");
	//debugString->AddString("direction: %f, %f,%f", m_enemy->Getforward().x, m_enemy->Getforward().y, m_enemy->Getforward().z);
	//debugString->AddString("EyePos: %f, %f,%f", m_cameraManager->GetTPSCamera()->GetEyePosition().x, m_cameraManager->GetTPSCamera()->GetEyePosition().y, m_cameraManager->GetTPSCamera()->GetEyePosition().z);
	//debugString->AddString("Pos: %f, %f", m_player->GetPos().x, m_player->GetPos().z);
	//debugString->AddString("Pos: %f, %f", m_enemy->GetPos().x, m_enemy->GetPos().z);
	//debugString->AddString("IsLockOn: %d ", m_lockOn->GetIsLOckOn());

	debugString->AddString("EyePos : %f,%f,%f", m_player->GetTPS_Camera()->GetCameraForward().x, m_player->GetTPS_Camera()->GetCameraForward().y, m_player->GetTPS_Camera()->GetCameraForward().z);
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayScene::Finalize()
{
	// do nothing.
}

//---------------------------------------------------------
// ���̃V�[��ID���擾����
//---------------------------------------------------------
IScene::SceneID PlayScene::GetNextSceneID() const
{

	//None�Ȃ�؂�ւ����Ȃ�
	return m_nextScene;

}



