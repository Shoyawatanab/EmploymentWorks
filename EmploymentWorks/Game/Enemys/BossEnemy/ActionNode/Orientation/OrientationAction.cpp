/*
	@file	OrientationAction.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "OrientationAction.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Params.h"
#include "Game/Observer/Messenger.h"

#include "OrientationAction.h"
#include "Game/Entities/BaseEntity.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="own">���L��</param>
/// <param name="target">�^�[�Q�b�g</param>
OrientationAction::OrientationAction(CommonResources* resources
	, BaseEntity* own
	, BaseEntity* target)
	:
	m_commonResources{resources}
	,m_own{own}
	,m_target{target}
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
OrientationAction::~OrientationAction()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
void OrientationAction::Initialize()
{

}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�p�����I����</returns>
OrientationAction:: ActionState OrientationAction::Update(const float& elapsedTime)
{

	//������������
	DirectX::SimpleMath::Vector3 direction = m_target->GetPosition() - m_own->GetPosition();
	direction.Normalize();
	//���̓G�̑O����
	DirectX::SimpleMath::Vector3 forward = Vector3::Transform(Vector3::Backward, m_own->GetRotation());
	//forward.Normalize();
	//��]���̍쐬
	DirectX::SimpleMath::Vector3 moveAxis = forward.Cross(direction);

	if (moveAxis.y >= 0.0f)
	{
		//���Ȃ�����
		moveAxis = DirectX::SimpleMath::Vector3::Up;
	}
	else
	{
		//���Ȃ牺����
		moveAxis = DirectX::SimpleMath::Vector3::Down;
	}

	//�p�x�����߂�
	float moveAngle = forward.Dot(direction);


	//���W�A���l�ɕϊ�
	moveAngle = acosf(moveAngle);

	//�p�x�Ƒ��x�̔�r�ŏ������ق����擾
	moveAngle = std::min(moveAngle, Params::BOSSENEMY_ROTATION_SPEED * elapsedTime);

	//�G�̉�]�̎擾
	DirectX::SimpleMath::Quaternion Rotate = m_own->GetRotation();
	//Y���ɑ΂��ĉ�]��������
	Rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(moveAxis, moveAngle);
	m_own->SetRotation(Rotate);


	// �G�̍��̑O�������X�V
	forward = Vector3::Transform(Vector3::Backward, m_own->GetRotation());
	forward.Normalize();

	// �v���C���[�����Ƃ̍����Čv�Z
	float alignment = forward.Dot(direction);

	// �p�x���������i�����Ă���j�Ȃ�ǉ�����
	const float threshold = cosf(DirectX::XMConvertToRadians(Params::ENEMY_PERMISSIBLE_ANGLE)); // 5�x�ȓ��Ȃ�OK�Ƃ���

	if (alignment >= threshold)
	{
		return ActionState::END;
	}



	return ActionState::RUNNING;


}


/// <summary>
/// ��Ԃɓ�������
/// </summary>
void OrientationAction::Enter()
{


}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void OrientationAction::Exit()
{
}
