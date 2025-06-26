/*
	@file	OrientationAction.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "OrientationAction.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Params.h"
#include "GameBase/Component/Components.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="own">���L��</param>
/// <param name="target">�^�[�Q�b�g</param>
OrientationAction::OrientationAction(Actor* own
	, Actor* target)
	:
	m_commonResources{}
	,m_own{own}
	,m_target{target}
{
	m_commonResources = CommonResources::GetInstance();


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
OrientationAction::~OrientationAction()
{
	// do nothing.
}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�p�����I����</returns>
OrientationAction:: ActionState OrientationAction::Update(const float& elapsedTime)
{
	using namespace DirectX::SimpleMath;

	auto ownerPosition = m_own->GetTransform()->GetPosition();

	auto targetPosition = m_target->GetTransform()->GetPosition();

	ownerPosition.y = 0.0f;
	targetPosition.y = 0.0f;

	//������������
	Vector3 direction = targetPosition - ownerPosition;
	direction.Normalize();
	//���̓G�̑O����
	Vector3 forward = m_own->GetTransform()->GetForwardVector();
	//forward.Normalize();
	//��]���̍쐬
	Vector3 moveAxis = forward.Cross(direction);

	if (moveAxis.y >= 0.0f)
	{
		//���Ȃ�����
		moveAxis = Vector3::Up;
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
	DirectX::SimpleMath::Quaternion Rotate = m_own->GetTransform()->GetRotate();
	//Y���ɑ΂��ĉ�]��������
	Rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(moveAxis, moveAngle);
	m_own->GetTransform()->SetRotate(Rotate);


	//// �G�̍��̑O�������X�V
	forward = m_own->GetTransform()->GetForwardVector();
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
