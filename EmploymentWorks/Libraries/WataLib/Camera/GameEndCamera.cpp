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



//-------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------
WataLib::GameEndCamera::GameEndCamera()
	:
	m_view{},
	m_projection{},
	m_eye{},
	m_target{ TARGET },
	m_up{ DirectX::SimpleMath::Vector3::UnitY },
	m_angle{},
	m_character{}
	,m_rotation{}
{

}

void WataLib::GameEndCamera::AddPointer(EnemyManager* enemyManger)
{
	m_enemyManager = enemyManger;
}

void WataLib::GameEndCamera::Initialize(CommonResources* resources)
{
	m_angle = 0;

	CalculateEyePosition();
	CalculateViewMatrix();
	CalculateProjectionMatrix();

}

//-------------------------------------------------------------------
// �X�V����
//-------------------------------------------------------------------
void WataLib::GameEndCamera::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	using namespace DirectX;
	using namespace DirectX::SimpleMath;



	// �J�������W���v�Z����
	CalculateEyePosition();
	// �r���[�s����X�V����
	CalculateViewMatrix();

}




//-------------------------------------------------------------------
// �r���[�s����v�Z����
//-------------------------------------------------------------------
void WataLib::GameEndCamera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

//-------------------------------------------------------------------
// �v���W�F�N�V�����s����v�Z����
//-------------------------------------------------------------------
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

//-------------------------------------------------------------------
// �J�������W���v�Z����
//-------------------------------------------------------------------
void WataLib::GameEndCamera::CalculateEyePosition()
{

	// ����̐i�s�����x�N�g��
	DirectX::SimpleMath::Vector3 forward;

	// �J�������^�[�Q�b�g����ǂꂭ�炢����Ă��邩
	forward = DirectX::SimpleMath::Vector3(-6,4,15);

	// �^�[�Q�b�g�̌����Ă�������ɑΉ�������
	forward = DirectX::SimpleMath::Vector3::Transform(forward, m_rotation);
	// �J�������W���v�Z����
	m_eye = m_target + forward;

}


void WataLib::GameEndCamera::Enter()
{

	m_target = m_enemyManager->GetLastEnemy()->GetPosition();
	
	m_rotation = m_enemyManager->GetLastEnemy()->GetRotation();

}


void WataLib::GameEndCamera::Exit()
{

}

void WataLib::GameEndCamera::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
}

