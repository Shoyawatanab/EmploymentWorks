/*
	@file	WalkingAction.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "WalkingAction.h"
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

#include "WalkingAction.h"
#include "Game/Entities/CharacterEntity.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
WalkingAction::WalkingAction(CommonResources* resources
	, CharacterEntity* own
	, CharacterEntity* target)
	:
	m_commonResources{resources}
	,m_own{own}
	,m_target{target}
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
WalkingAction::~WalkingAction()
{
	// do nothing.
}

void WalkingAction::Initialize()
{

}

WalkingAction:: ActionState WalkingAction::Update(const float& elapsedTime)
{

//��]
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


//�ړ�
	//�v���C���̍��W�̎擾
	Vector3 targetPosition = m_target->GetPosition();

	Vector3 ownPosition = m_own->GetPosition();

	//���������߂�
	direction = targetPosition - ownPosition;
	//���K��
	direction.Normalize();

	direction *= Params::BOSSENEMY_MOVE_SPEED * elapsedTime;

	m_own->SetPosition(ownPosition + direction);

	//�A�j���[�V�����̎��Ԃɍ��킹��
	if (m_time >= 4.0f)
	{
		return ActionState::End;
	}

	m_time += elapsedTime;

	return ActionState::Running;

}



void WalkingAction::Enter()
{

	m_own->ChangeAnimation("Move");

	m_time = 0;
}

void WalkingAction::Exit()
{
}
