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



	m_enemy = std::make_unique<Enemy>();
	m_player = std::make_unique<Player>();
	m_cameraManager = std::make_unique<mylib::GameCameraManager>();

	m_floor = std::make_unique<Floor>();
	for (int i = 0; i < 4; i++)
	{
		auto wall = std::make_unique<Wall>();
		m_wall.push_back(std::move(wall));
	}

	for (int i = 0; i < 2; i++)
	{
		auto pillar = std::make_unique<Pillar>();
		m_pillar.push_back(std::move(pillar));
	}

	m_ceiling = std::make_unique<Ceiling>();

	for (int i = 0; i < 1; i++)
	{
		auto artillery = std::make_unique<Artillery>();
		m_artillery.push_back(std::move(artillery));

	}


	m_lockOn = std::make_unique<LockOn>();
	m_collisionManager = std::make_unique<CollisionManager>();
	m_ui = std::make_unique<UI>();

	//�΁@��
	auto rock = std::make_unique<Rock>();
	rock->Initialize(m_commonResources, Vector3(15, 0, 0), Vector3(3.8, 3.5f, 2.5f), Vector3(0,0,0));
	m_rock.emplace_back(std::move(rock));

	rock = std::make_unique<Rock>();
	rock->Initialize(m_commonResources, Vector3(-15, 0, 0), Vector3(3.8, 3.5f, 2.5f), Vector3(0,0,0));
	m_rock.emplace_back(std::move(rock));

	//�e�N���X�ɕK�v�ȃN���X�̃C���X�^���X
	m_player->Instances();
	m_enemy->Instances();
	m_cameraManager->Instances();
	m_ui->Instances();


	//�e�N���X�̏���o�^�ƃC���X�^���X
	m_player->RegistrationInformation(m_enemy.get());
	m_enemy->RegistrationInformation(m_player.get());
	m_cameraManager->RegistrationInformation(this, m_player.get(), m_enemy.get());
	m_lockOn->RegistrationInformation(m_player.get(), m_enemy.get(), m_cameraManager.get());
	m_ui->RegistrationInformation(this, m_player.get(), m_enemy.get());


	Vector3 floorScale = Vector3(70, 0.1f, 50);
	float height = 20.0f;

	

	m_floor->Initialize(m_commonResources, Vector3::Zero, floorScale,Vector3(0,0,0));
	m_player->Initialize(m_commonResources, Vector3(0, 3.75f, 10));
	m_enemy->Initialize(m_commonResources, Vector3(0, 5.75f, -10));
	//Wall�N���X�͓����蔻��������Ă��邾�����f���̕`��͂Ȃ�
	m_wall[0]->Initialize(m_commonResources, Vector3(-floorScale.x, 0, 0), Vector3(1, height, floorScale.z),Vector3(0,0,0));
	m_wall[1]->Initialize(m_commonResources, Vector3(floorScale.x, 0, 0), Vector3(1, height, floorScale.z),Vector3(0, 0, 0));
	m_wall[2]->Initialize(m_commonResources, Vector3(0, 0, -floorScale.z), Vector3(floorScale.x, height, 1),Vector3(0, 0, 0));
	m_wall[3]->Initialize(m_commonResources, Vector3(0, 0, floorScale.z), Vector3(floorScale.x, height, 1),Vector3(0, 0, 0));

	m_pillar[0]->Initialize(m_commonResources, Vector3(0,1,0), Vector3(2, 5, 2),Vector3::Zero);
	m_pillar[1]->Initialize(m_commonResources, Vector3(-8, 1, 0), Vector3(2, 5, 2), Vector3(0, 0, 0));

	m_artillery[0]->Initialize(m_commonResources, Vector3(0, 1, 5), Vector3(1, 1, 1),Vector3(90,0,90));

	m_ceiling->Initialize(m_commonResources,Vector3(0,height,0),floorScale,Vector3(0,0,0));
	
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

	m_rock[0]->RegistrationCollionManager(m_collisionManager.get());
	m_rock[1]->RegistrationCollionManager(m_collisionManager.get());


	//Ray�Ƃ̓����蔻�����邽�߂�Bounding�̓o�^
	m_commonResources->GetJudgement()->SetBounding(m_rock[0]->GetBounding());
	m_commonResources->GetJudgement()->SetBounding(m_rock[1]->GetBounding());


	m_sky = std::make_unique<Sky>();
	m_sky->Initialize(m_commonResources);

	m_state = GameState::None;
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
				//m_enemy->Update(elapsedTime);
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
				m_enemy->ReduceSize(elapsedTime);
			}

			//�G��|�����Ƃ��̃A�j���[�V�������I�������
			if (m_enemy->GetScale() <= 0 && m_ui->GetCurrentUIState() != m_ui->GetGameClearUI())
			{
				m_ui->ChangeState(m_ui->GetGameClearUI());
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



	m_player->Update(elapsedTime, m_cameraManager->GetTPSCamera()->GetRotationX());

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

	m_ceiling->Render(view, m_projection);

	m_enemy->Render(view, m_projection);


	for (auto& rock : m_rock)
	{
		//rock->Render(view, m_projection);
	}

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

	debugString->AddString("index : %d", m_player->GetUsingBoomerangIndex());
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



