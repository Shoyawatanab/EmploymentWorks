#include "pch.h"
#include "BoomerangBounce.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="stateMahine">�X�e�[�g�}�V�[��</param>
/// <param name="boomerang">�u�[������</param>
/// <param name="player">�v���C��</param>
BoomerangBounce::BoomerangBounce(BoomerangStateMachine* stateMahine, Boomerang* boomerang)
	:
	m_stateMahine{ stateMahine }
	, m_boomerang{ boomerang }
	,m_bounceDirection{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoomerangBounce::~BoomerangBounce()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangBounce::Update(const float& deltaTime)
{

	auto position = m_boomerang->GetTransform()->GetWorldPosition();

	position += m_bounceDirection * BOUNCE_POWER *  deltaTime;

	m_boomerang->GetTransform()->SetPosition(position);


}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BoomerangBounce::Enter()
{
	//���W�b�g�{�f�B�[�̗L��
	m_boomerang->GetComponent<RigidbodyComponent>()->SetActive(true);
	//���˕Ԃ���������߂�
	m_bounceDirection = m_boomerang->GetTransform()->GetWorldPosition() - m_boomerang->GetLastPosition();

}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BoomerangBounce::Exit()
{
}
