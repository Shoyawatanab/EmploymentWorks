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
#include "Game/Screen.h"


#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/BossEnemy.h"
#include "Libraries/MyLib/Camera/TPS_Camera.h"
#include "Libraries/MyLib/Camera/GameCameraManager.h"

const float LOCKONDISTANCE = 20.0f;
//����p
const float VIEWANGLE = 60.0f;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
LockOn::LockOn()
	:
	m_windowHeight(0)
	, m_windowWidth(0)
	, m_pDR(nullptr),
	m_player{}
	, m_enemy{}
	, m_tpsCamera{ }
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
	Add(L"Resources/Textures/LockOnTex.png"
		, Vector2(300, 300)
		, Vector2(0.3f, 0.3f)
		, ANCHOR::MIDDLE_CENTER);

	m_isLockOn = false;

}

//

/// <summary>
/// �͈͓��̃I�u�W�F�N�g��T��
/// </summary>
/// <param name="points">���W�̔z��</param>
/// <param name="center">���S���W</param>
/// <param name="range">���a</param>
/// <returns>�͈͓��̍��W</returns>
DirectX::SimpleMath::Vector2 LockOn::FilterWithinRange(const std::vector<DirectX::SimpleMath::Vector3>& points, const DirectX::SimpleMath::Vector2& center, float range)
{

	using namespace DirectX::SimpleMath;
	//�ϐ��錾
	DirectX::SimpleMath::Vector2 result = Vector2(-100, -100);

	float minLength = 1000;

	//
	for (const auto& point : points)
	{
		//���W���X�N���[�����W�ɕϊ�
		Vector2 ScreenPos = WorldToScreen(point,
			Matrix::Identity,
			m_tpsCamera->GetViewMatrix(),
			m_tpsCamera->GetProjectionMatrix(),
			m_windowWidth,
			m_windowHeight
		);

		float distance = Vector2::Distance(ScreenPos, center);

		//raneg���̍��W���ǂ����̔���
		if (distance <= range)
		{
			//�ŏ��l�������������
			if (minLength > distance)
			{

				//�z��Ɋi�[
				result = ScreenPos;
				//�ŏ��l���X�V
				minLength = distance;
				//�^�[�Q�b�g���X�V
				m_target = point;

			}

		}
	}

	return result;

}
//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void LockOn::Update(float elapsedTime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	UNREFERENCED_PARAMETER(elapsedTime);

	//���b�N�I���̃��Z�b�g
	m_isLockOn = false;

	//�u�[���������\���Ă��Ȃ��Ȃ�
	if (m_player->GetUsingBoomerang()->GetBoomerangState() != m_player->GetUsingBoomerang()->GetBoomerangGetReady())
	{
		return;
	}

	std::vector<DirectX::SimpleMath::Vector3> positions;

	for (auto& object : m_targetObject)
	{
		positions.push_back(object->GetPosition());
	}

	DirectX::SimpleMath::Vector2 center = Vector2(Screen::CENTER_X, Screen::CENTER_Y);

	DirectX::SimpleMath::Vector2 result = FilterWithinRange(positions, center, 200.0f);

	if (result == Vector2(-100, -100))
	{
		return;
	}


	DirectX::SimpleMath::Vector2 minPosition;

	m_isLockOn = true;

	m_userInterface[0]->SetPosition(result);

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

void LockOn::RegistrationInformation(Player* player, Enemy* enemy, mylib::GameCameraManager* gameCamera)
{

	m_player = player;
	m_enemy = enemy;
	m_tpsCamera = gameCamera->GetTPSCamera();

}

void LockOn::Instances()
{



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
		, anchor
		, UserInterface::Kinds::LockOn);
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



/// <summary>
///  �G���v���C���̎��E�ɓ����Ă��邩�ǂ���
/// </summary>
/// <param name="playerPos">�v���C�����W</param>
/// <param name="playerForward">�v���C���̌����Ă������</param>
/// <param name="enemyPos">�G���W</param>
/// <returns></returns>
bool LockOn::IsEnemyInview(const DirectX::SimpleMath::Vector3& playerPos, const DirectX::SimpleMath::Vector3& playerForward, const DirectX::SimpleMath::Vector3& enemyPos)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	//�p�x�����W�A���ɕϊ�
	float radianViewAngle = XMConvertToRadians(VIEWANGLE);
	float cosViewAngle = cos(radianViewAngle / 2);

	//�G�ւ̃x�N�g���̌v�Z
	Vector3 enemyVector = enemyPos - playerPos;
	enemyVector.Normalize();

	//�h�b�g�ς̌v�Z
	float dotProduct = enemyVector.Dot(playerForward);

	return dotProduct >= cosViewAngle;

}



