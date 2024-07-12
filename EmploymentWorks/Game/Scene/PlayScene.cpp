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

#include "Libraries/MyLib/TPS_Camera.h"
#include "Game/Object/Player.h"
#include "Game/Object/Enemy.h"
#include "Game/Object/Floor.h"
#include "Game/LockOn.h"
#include "Game/DetectionCollision/CollisionManager.h"
#include "Game/Object/Wall.h"

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
	m_isChangeScene{},
	m_player{},
	m_enemy{},
	m_tpsCamera{},
	m_floor{}
	, m_lockOn{}

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
		0.1f, 100.0f
	);

	m_floor = std::make_unique<Floor>();
	m_enemy = std::make_unique<Enemy>();
	m_player = std::make_unique<Player>(m_enemy.get());
	m_tpsCamera = std::make_unique<mylib::TPS_Camera>(m_player.get());

	for (int i = 0; i < WALLSIZE; i++)
	{
		m_wall.push_back(std::make_unique<Wall>());
	}


	m_floor->Initialize(m_commonResources, Vector3::Zero, Vector3(15, 0.6f, 15), 8.0f);
	m_player->Initialize(m_commonResources, Vector3(0, 2.75f, 0));
	m_enemy->Initialize(m_commonResources, Vector3(0, 0.75f, -10));
	//Wall�N���X�͓����蔻��������Ă��邾�����f���̕`��͂Ȃ�
	m_wall[0]->Initialize(m_commonResources,
		Vector3(16, WALLHEITH, 0), Vector3(1.5f, 2, 15), 8.6f);
	m_wall[1]->Initialize(m_commonResources,
		Vector3(-16, WALLHEITH, 0), Vector3(1.5f, 2, 15), 8.6f);
	m_wall[2]->Initialize(m_commonResources,
		Vector3(0, WALLHEITH, 16), Vector3(15, 2, 1.5f), 8.6f);
	m_wall[3]->Initialize(m_commonResources,
		Vector3(0, WALLHEITH, -16), Vector3(15, 2, 1.5f), 8.6f);


	m_lockOn = std::make_unique<LockOn>(m_player.get(), m_enemy.get(), m_tpsCamera.get());
	m_lockOn->Initialize(m_commonResources->GetDeviceResources(),
		m_commonResources->GetDeviceResources()->GetOutputSize().right,
		m_commonResources->GetDeviceResources()->GetOutputSize().bottom);
	m_collisionManager = std::make_unique<CollisionManager>();


	///�����蔻���Manager�ɒǉ�
	m_player->RegistrationCollionManager(m_collisionManager.get());
	m_enemy->RegistrationCollionManager(m_collisionManager.get());
	m_floor->RegistrationCollionManager(m_collisionManager.get());

	for (auto& wall : m_wall)
	{
		wall->RegistrationCollionManager(m_collisionManager.get());
	}

	// �V�[���ύX�t���O������������
	m_isChangeScene = false;
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// �f�o�b�O�J�������X�V����
	//m_debugCamera->Update(m_commonResources->GetInputManager());

	m_tpsCamera->Update(elapsedTime);

	m_player->Update(elapsedTime,m_tpsCamera->GetRotationX());
	m_enemy->Update(elapsedTime);
	m_collisionManager->Update();


	m_lockOn->Update(elapsedTime);


	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	// �X�y�[�X�L�[�������ꂽ��
	//if (kbTracker->pressed.Space)
	//{
	//	m_isChangeScene = true;
	//}
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayScene::Render()
{
	using namespace DirectX::SimpleMath;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	// �r���[�s����擾����
	//const Matrix& view = m_debugCamera->GetViewMatrix();
	const Matrix& view = m_tpsCamera->GetViewMatrix();;


	// �i�q����`�悷��
	m_gridFloor->Render(context, view, m_projection);
	m_floor->Render(view, m_projection);

	for (auto& wall : m_wall)
	{
		wall->Render(view, m_projection);
	}



	m_player->Render(view, m_projection);
	m_enemy->Render(view, m_projection);

	m_lockOn->Render();


	// �f�o�b�O�����uDebugString�v�ŕ\������
	auto debugString = m_commonResources->GetDebugString();
	debugString->AddString("Play Scene");
	debugString->AddString("Pos: %d, %d", m_tpsCamera->GetAngle().x, m_tpsCamera->GetAngle().y);

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
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		return IScene::SceneID::TITLE;
	}
	if (m_enemy->GetHp() <= 0)
	{
		return IScene::SceneID::RESULT;
	}

	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}
