/*
	@file	TargetMarker.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "TargetMarker.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Game/Screen.h"
#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Observer/Messenger.h"
#include "Libraries/WataLib/UserInterface.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
TargetMarker::TargetMarker()
	:
	m_tpsCamera{ }
	, m_isTargetMarker{ false }
	,m_windowSize{}
	,m_marker{}
	,m_targetObject{}
	, m_isLockOn{false}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TargetMarker::~TargetMarker()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void TargetMarker::Initialize(CommonResources* resources)
{
	using namespace DirectX::SimpleMath;

	m_commonResources = resources;

	//��ʃT�C�Y�̎擾
	m_windowSize.first = m_commonResources->GetDeviceResources()->GetOutputSize().right;
	m_windowSize.second = m_commonResources->GetDeviceResources()->GetOutputSize().bottom;


	m_isTargetMarker = false;

	m_marker = std::make_unique<UserInterface>();
	m_marker->Create(m_commonResources->GetDeviceResources(), L"Resources/Textures/TargetMarker.png"
		,Vector2(200,200), Vector2(0.3f,0.3f));




	Messenger::Attach(EventParams::EventType::BoomerangGetReady, this);
	Messenger::Attach(EventParams::EventType::BoomerangGetReadyEnd, this);

}


/// <summary>
/// �͈͓��̃I�u�W�F�N�g��T��
/// </summary>
/// <param name="points">���W�̔z��</param>
/// <param name="center">���S���W</param>
/// <param name="range">���a</param>
/// <returns>�͈͓��̍��W</returns>
DirectX::SimpleMath::Vector2 TargetMarker::FilterWithinRange(const std::vector<DirectX::SimpleMath::Vector3>& points, const DirectX::SimpleMath::Vector2& center, float range)
{

	using namespace DirectX::SimpleMath;
	//�ϐ��錾
	DirectX::SimpleMath::Vector2 result;

	//��ʂ̉��̃T�C�Y�������l�Ƃ���
	float minLength = m_windowSize.first;

	m_isLockOn = false;

	//
	for (const auto& point : points)
	{
		//���W���X�N���[�����W�ɕϊ�
		Vector2 ScreenPos = WorldToScreen(point,
			Matrix::Identity,
			m_tpsCamera->GetViewMatrix(),
			m_tpsCamera->GetProjectionMatrix(),
			m_windowSize.first,
			m_windowSize.second
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
				
				m_isLockOn = true;

			}

		}
	}

	return result;

}


/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void TargetMarker::Update(float elapsedTime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	UNREFERENCED_PARAMETER(elapsedTime);

	m_target = Vector3::Zero;

	//�u�[���������\���Ă��Ȃ��Ȃ�
	if (!m_isTargetMarker)
	{
		return;
	}

	std::vector<DirectX::SimpleMath::Vector3> positions;

	for (auto& object : m_targetObject)
	{
		if(object->GetIsEntityActive())
		{
			positions.push_back(object->GetPosition());

		}

	}

	DirectX::SimpleMath::Vector2 center = Vector2(Screen::CENTER_X, Screen::CENTER_Y);

	DirectX::SimpleMath::Vector2 result = FilterWithinRange(positions, center, RANGE);


	m_marker->SetPosition(result);


}

/// <summary>
/// �`��
/// </summary>
void TargetMarker::Render()
{
	using namespace DirectX::SimpleMath;


	if (m_isLockOn && m_isTargetMarker)
	{
		m_marker->Render();

	}


}

/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="tpsCamera">TPS�J����</param>
void TargetMarker::AddPointer(WataLib::TPS_Camera* tpsCamera)
{

	m_tpsCamera = tpsCamera;

}


/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�C�x���g�̎��</param>
/// <param name="datas">�C�x���g�̃f�[�^</param>
void TargetMarker::Notify(EventParams::EventType type, void* datas)
{
	switch (type)
	{
		case EventParams::EventType::BoomerangGetReady:
			m_isTargetMarker = true;
			break;
		case EventParams::EventType::BoomerangGetReadyEnd:
			m_isTargetMarker = false;
			m_isLockOn = false;

			break;
		default:
			break;
	}

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
DirectX::SimpleMath::Vector2 TargetMarker::WorldToScreen(const DirectX::SimpleMath::Vector3& worldPos,
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







