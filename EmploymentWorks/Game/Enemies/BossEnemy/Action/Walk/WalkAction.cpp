/*
	�N���X��     : WalkAction
	����         : �{�X�G�̕������
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "WalkAction.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"
#include "GameBase/Common/Commons.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="own">���L��</param>
/// <param name="target">�^�[�Q�b�g</param>
WalkAction::WalkAction(BossEnemy* own
	, Actor* target)
	:
	m_own{own}
	,m_target{target}
	,m_time{}
{

	m_commonResources = CommonResources::GetInstance();

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
WalkAction::~WalkAction()
{
	// do nothing.
}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�p�����I����</returns>
WalkAction:: ActionState WalkAction::Update(const float& elapsedTime)
{
	using namespace DirectX::SimpleMath;

	auto animation = m_own->GetAnimation();

	animation->SetFloat("Move", 1.0f);

//��]
	//������������
	Vector3 direction = m_target->GetTransform()->GetPosition() - m_own->GetTransform()->GetPosition();
	direction.Normalize();
	//���̓G�̑O����
	Vector3 forward = Vector3::Transform(Vector3::Backward, m_own->GetTransform()->GetRotate());
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
		moveAxis = Vector3::Down;
	}

	//�p�x�����߂�
	float moveAngle = forward.Dot(direction);


	//���W�A���l�ɕϊ�
	moveAngle = acosf(moveAngle);

	//�p�x�Ƒ��x�̔�r�ŏ������ق����擾
	moveAngle = std::min(moveAngle, Params::BOSSENEMY_ROTATION_SPEED * elapsedTime);

	//�G�̉�]�̎擾
	Quaternion Rotate = m_own->GetTransform()->GetRotate();
	//Y���ɑ΂��ĉ�]��������
	Rotate *= Quaternion::CreateFromAxisAngle(moveAxis, moveAngle);
	m_own->GetTransform()->SetRotate(Rotate);


//�ړ�
	//�v���C���̍��W�̎擾
	Vector3 targetPosition = m_target->GetTransform()->GetPosition();

	Vector3 ownPosition = m_own->GetTransform()->GetPosition();

	//���������߂�
	direction = targetPosition - ownPosition;
	//���K��
	direction.Normalize();

	direction *= Params::BOSSENEMY_MOVE_SPEED * elapsedTime;

	m_own->GetTransform()->SetPosition(ownPosition + direction);

	//�A�j���[�V�����̎��Ԃɍ��킹��
	if (m_time >= WALK_TIME)
	{
		return ActionState::END;
	}

	m_time += elapsedTime;

	return ActionState::RUNNING;

}


/// <summary>
/// ��Ԃɓ�������
/// </summary>
void WalkAction::Enter()
{
	m_time = 0;
}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void WalkAction::Exit()
{
}
