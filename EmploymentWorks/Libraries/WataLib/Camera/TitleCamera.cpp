/*
	@file	TitleCamera.cpp
	@brief	TPS�J�����N���X
*/
#include "pch.h"
#include "TitleCamera.h"
#include "Game/Screen.h"


const int MAXANGLEY = 100;
const DirectX::SimpleMath::Vector3 TARGET = DirectX::SimpleMath::Vector3(0, 1, 0); //�X�e�[�W�̒��S

const float MOVESPEED = 0.5f;




/// <summary>
/// �R���X�g���N�^
/// </summary>
WataLib::TitleCamera::TitleCamera()
	:
	m_view{},
	m_projection{},
	m_eye{},
	m_target{ TARGET },
	m_up{ DirectX::SimpleMath::Vector3::UnitY },
	m_angle{}
{


}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void WataLib::TitleCamera::Initialize(CommonResources* resources)
{
	UNREFERENCED_PARAMETER(resources);


	CalculateEyePosition(0);
	CalculateViewMatrix();
	CalculateProjectionMatrix();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void WataLib::TitleCamera::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();


	// �J�������W���v�Z����
	CalculateEyePosition(elapsedTime);
	// �r���[�s����X�V����
	CalculateViewMatrix();




}

/// <summary>
// �r���[�s��̌v�Z
/// </summary>
void WataLib::TitleCamera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

/// <summary>
/// �v���W�F�N�V�����s��̌v�Z
/// </summary>
void WataLib::TitleCamera::CalculateProjectionMatrix()
{
	// �E�B���h�E�T�C�Y
	const float width = static_cast<float>(Screen::WIDTH);
	const float height = static_cast<float>(Screen::HEIGHT);

	// ��ʏc����
	const float aspectRatio = width / height;

	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);

}

/// <summary>
/// �J�������W�̌v�Z
/// </summary>
void WataLib::TitleCamera::CalculateEyePosition(const float& elapsedTime)
{

	m_angle += ROTATION_SPEED * elapsedTime;
	float x = DISTANCE_TO_TARGET.x * cosf(m_angle);
	float z = DISTANCE_TO_TARGET.z * sinf(m_angle);

	m_eye = DirectX::SimpleMath::Vector3(x, DISTANCE_TO_TARGET.y, z);

}


/// <summary>
/// ��Ԃɓ�������
/// </summary>
void WataLib::TitleCamera::Enter()
{
}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void WataLib::TitleCamera::Exit()
{

}

void WataLib::TitleCamera::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	assert(&view);
	assert(&projection);



}

