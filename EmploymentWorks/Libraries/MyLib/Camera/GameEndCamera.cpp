/*
	@file	GameEndCamera.cpp
	@brief	TPS�J�����N���X
*/
#include "pch.h"
#include "GameEndCamera.h"
#include "Game/Screen.h"
#include "Libraries/MyLib/Mouse.h"
#include "Game/Object/Enemy/Enemy.h"
#include "Libraries/MyLib/Camera/GameCameraManager.h"

const DirectX::SimpleMath::Vector3 TARGET = DirectX::SimpleMath::Vector3(0, 1, 0); //�X�e�[�W�̒��S

const float MAXTIME = 4;



//-------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------
mylib::GameEndCamera::GameEndCamera(GameCameraManager* cameraManager, Enemy* enemy)
	:
	m_view{},
	m_projection{},
	m_eye{},
	m_target{ TARGET },
	m_up{ DirectX::SimpleMath::Vector3::UnitY },
	m_angle{},
	m_enemy{enemy},
	m_cameraManager{cameraManager}
{

	CalculateEyePosition();
	CalculateViewMatrix();
	CalculateProjectionMatrix();
}

void mylib::GameEndCamera::Initialize()
{
	m_angle = 0;
	m_target = m_enemy->GetPos();
}

//-------------------------------------------------------------------
// �X�V����
//-------------------------------------------------------------------
void mylib::GameEndCamera::Update(const float& elapsedTime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	m_target = m_enemy->GetPos();


	// �J�������W���v�Z����
	CalculateEyePosition();
	// �r���[�s����X�V����
	CalculateViewMatrix();

}




//-------------------------------------------------------------------
// �r���[�s����v�Z����
//-------------------------------------------------------------------
void mylib::GameEndCamera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

//-------------------------------------------------------------------
// �v���W�F�N�V�����s����v�Z����
//-------------------------------------------------------------------
void mylib::GameEndCamera::CalculateProjectionMatrix()
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
void mylib::GameEndCamera::CalculateEyePosition()
{


	// ����̐i�s�����x�N�g��
	DirectX::SimpleMath::Vector3 forward = m_enemy->Getforward();

	// �J�������^�[�Q�b�g����ǂꂭ�炢����Ă��邩
	forward = DirectX::SimpleMath::Vector3(-6,4,15);

	//�G�̉�]���擾
	DirectX::SimpleMath::Quaternion enemyRotate = m_enemy->GetRotate();

	// �^�[�Q�b�g�̌����Ă�������ɑΉ�������
	forward = DirectX::SimpleMath::Vector3::Transform(forward, enemyRotate);
	// �J�������W���v�Z����
	m_eye = m_target + forward;

}



void mylib::GameEndCamera::Enter()
{
}


void mylib::GameEndCamera::Exit()
{

}

