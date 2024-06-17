/*
	@file	TPS_Camera.cpp
	@brief	TPS�J�����N���X
*/
#include "pch.h"
#include "TPS_Camera.h"
#include "Game/Screen.h"
#include "Game/Object/Player.h"

//-------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------
mylib::TPS_Camera::TPS_Camera(Player* player)
	:
	m_view{},
	m_projection{},
	m_eye{},
	m_target{},
	m_up{ DirectX::SimpleMath::Vector3::UnitY },
	m_player{player}
{
	CalculateEyePosition(DirectX::SimpleMath::Quaternion::Identity);
	CalculateViewMatrix();
	CalculateProjectionMatrix();
}

//-------------------------------------------------------------------
// �X�V����
//-------------------------------------------------------------------
void mylib::TPS_Camera::Update(float elapsedTime)
{
	// target�̈ʒu���X�V����
	m_target = m_player->GetPosition();

	// �J�������W���v�Z����
	CalculateEyePosition(m_player->GetRotate());
	// �r���[�s����X�V����
	CalculateViewMatrix();
}

//-------------------------------------------------------------------
// �r���[�s����v�Z����
//-------------------------------------------------------------------
void mylib::TPS_Camera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

//-------------------------------------------------------------------
// �v���W�F�N�V�����s����v�Z����
//-------------------------------------------------------------------
void mylib::TPS_Camera::CalculateProjectionMatrix()
{
	// �E�B���h�E�T�C�Y
	const float width = static_cast<float>(Screen::WIDTH);
	const float height = static_cast<float>(Screen::HEIGHT);
	
	// ��ʏc����
	const float aspectRatio = width / height;

	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);
}

//-------------------------------------------------------------------
// �J�������W���v�Z����
//-------------------------------------------------------------------
void mylib::TPS_Camera::CalculateEyePosition(const DirectX::SimpleMath::Quaternion& rotate)
{
	// ����̐i�s�����x�N�g��
	DirectX::SimpleMath::Vector3 forward = DirectX::SimpleMath::Vector3::Forward;

	// �J�������^�[�Q�b�g����ǂꂭ�炢����Ă��邩
	forward.y = CAMERA_HIGHT;
	forward.z = CAMERA_DISTANCE;

	// �^�[�Q�b�g�̌����Ă�������ɒǏ]����
	forward = DirectX::SimpleMath::Vector3::Transform(forward, rotate);

	// �J�������W���v�Z����
	m_eye = m_target + forward;
}
