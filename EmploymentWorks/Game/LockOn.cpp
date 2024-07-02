/*
	@file	LockOn.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "LockOn.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Object/Player.h"
#include "Game/Object/Enemy.h"
#include "Libraries/MyLib/TPS_Camera.h"

const float LOCKONDISTANCE = 10.0f;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
LockOn::LockOn(Player* player, Enemy* enemy, mylib::TPS_Camera* tpsCamera)
	:
	m_windowHeight(0)
	, m_windowWidth(0)
	, m_pDR(nullptr),
	m_player{player}
	,m_enemy{enemy}
	,m_tpsCamera{tpsCamera}
	, m_isLockOn{ false }

{
	m_userInterface.clear();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
LockOn::~LockOn()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void LockOn::Initialize(DX::DeviceResources* pDR, int width, int height)
{
	using namespace DirectX::SimpleMath;
	assert(pDR);

	m_pDR = pDR;
	m_windowWidth = width;
	m_windowHeight = height;

	//  �w�i�ƂȂ�E�B���h�E�摜��ǂݍ���

	//  ���摜��ǂݍ���
	Add(L"Resources/Textures/Reticle.jpg"
		,Vector2(300, 300)
		,Vector2(0.1f, 0.1f)
		,ANCHOR::MIDDLE_CENTER);
	m_isLockOn = false;

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void LockOn::Update(float elapsedTime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	UNREFERENCED_PARAMETER(elapsedTime);




	if (m_player->GetBoomerang()->GetBoomerangState() != m_player->GetBoomerang()->GetBoomerangGetReady())
	{
		return;
	}



	Vector3 PlayerPos = m_player->GetPosition();
	Vector3 EnemyPos = m_enemy->GetPosition();

	Vector3 Distance = PlayerPos - EnemyPos;


	if (Distance.Length() >= LOCKONDISTANCE)
	{
		m_isLockOn = false;
		return;
	}

	m_isLockOn = true;


	Vector2 ScreenPos = WorldToScreen(m_enemy->GetPosition(),
		Matrix::Identity,
		m_tpsCamera->GetViewMatrix(),
		m_tpsCamera->GetProjectionMatrix(),
		m_windowWidth,
		m_windowHeight
		);

	m_userInterface[0]->SetPosition(ScreenPos);

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void LockOn::Render()
{
	using namespace DirectX::SimpleMath;

	if (!m_isLockOn)
	{
		return;
	}


	for (int i = 0; i < m_userInterface.size(); i++)
	{
		m_userInterface[i]->Render();
	}
}


void LockOn::Add(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor)
{
	//  ���j���[�Ƃ��ăA�C�e����ǉ�����
	std::unique_ptr<UserInterface> userInterface = std::make_unique<UserInterface>();
	//  �w�肳�ꂽ�摜��\�����邽�߂̃A�C�e�����쐬����
	userInterface->Create(m_pDR
		, path
		, position
		, scale
		, anchor);
	userInterface->SetWindowSize(m_windowWidth, m_windowHeight);

	//  �A�C�e����V�����ǉ�
	m_userInterface.push_back(std::move(userInterface));





}

/// <summary>
/// ���[���h���W���X�N���[�����W�ɕϊ�
/// </summary>
/// <param name="worldPos">���[���h���W</param>
/// <param name="worldMatrix">���[���h�̍s��</param>
/// <param name="viewMatrix"></param>
/// <param name="projectionMatrix"></param>
/// <param name="screenWidth"></param>
/// <param name="screenHeight"></param>
/// <returns></returns>
DirectX::SimpleMath::Vector2 LockOn::WorldToScreen(const DirectX::SimpleMath::Vector3& worldPos, 
	const DirectX::SimpleMath::Matrix& worldMatrix,
	const DirectX::SimpleMath::Matrix& viewMatrix,
	const DirectX::SimpleMath::Matrix& projectionMatrix,
	int screenWidth, int screenHeight)
{
	using namespace DirectX::SimpleMath;
	// ���[���h���W��ϊ����邽�߂̍s�������
	Matrix transformMatrix = worldMatrix * viewMatrix * projectionMatrix;

	// ���[���h���W���v���W�F�N�V������Ԃɕϊ�
	Vector3 projectedPos = Vector3::Transform(worldPos, transformMatrix);

	// �ˉe���ꂽ���W���X�N���[�����W�ɕϊ�
	float x = (projectedPos.x / projectedPos.z * 0.5f + 0.5f) * screenWidth;
	float y = (0.5f - projectedPos.y / projectedPos.z * 0.5f) * screenHeight;

	return Vector2(x, y);

}

