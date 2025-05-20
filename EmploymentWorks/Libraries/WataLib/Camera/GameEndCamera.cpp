/*
	@file	GameEndCamera.cpp
	@brief	TPS�J�����N���X
*/
#include "pch.h"
#include "GameEndCamera.h"
#include "Game/Screen.h"
#include "Game/Enemys/EnemyManager.h"

const DirectX::SimpleMath::Vector3 TARGET = DirectX::SimpleMath::Vector3(0, 1, 0); //�X�e�[�W�̒��S

const float MAXTIME = 4;



/// <summary>
/// �R���X�g���N�^
/// </summary>
WataLib::GameEndCamera::GameEndCamera()
	:
	m_view{},
	m_projection{},
	m_eye{},
	m_target{ TARGET },
	m_up{ DirectX::SimpleMath::Vector3::UnitY },
	m_angle{}
	,m_rotation{}
	,m_enemyManager{}
{

}

void WataLib::GameEndCamera::AddPointer(EnemyManager* enemyManger)
{
	m_enemyManager = enemyManger;
}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">�o�ߎ���</param>
void WataLib::GameEndCamera::Initialize(CommonResources* resources)
{
	UNREFERENCED_PARAMETER(resources);
	m_angle = 0;

	CalculateEyePosition();
	CalculateViewMatrix();
	CalculateProjectionMatrix();

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void WataLib::GameEndCamera::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	// �J�������W���v�Z����
	CalculateEyePosition();
	// �r���[�s����X�V����
	CalculateViewMatrix();

}




/// <summary>
/// �r���[�s��̌v�Z
/// </summary>
void WataLib::GameEndCamera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

/// <summary>
/// �ˉe�s��̌v�Z
/// </summary>
void WataLib::GameEndCamera::CalculateProjectionMatrix()
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
void WataLib::GameEndCamera::CalculateEyePosition()
{

	// ����̐i�s�����x�N�g��
	DirectX::SimpleMath::Vector3 forward;

	// �^�[�Q�b�g�̌����Ă�������ɑΉ�������
	forward = DirectX::SimpleMath::Vector3::Transform(DISTANCE_TO_TARGET, m_rotation);
	// �J�������W���v�Z����
	m_eye = m_target + forward;

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void WataLib::GameEndCamera::Enter()
{

	m_target = m_enemyManager->GetLastEnemy()->GetPosition();
	
	m_rotation = m_enemyManager->GetLastEnemy()->GetRotation();

}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void WataLib::GameEndCamera::Exit()
{

}

void WataLib::GameEndCamera::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);


}

