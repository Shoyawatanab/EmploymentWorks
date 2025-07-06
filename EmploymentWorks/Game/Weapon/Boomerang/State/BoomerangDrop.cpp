#include "pch.h"
#include "BoomerangDrop.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="stateMahine">�X�e�[�g�}�V�[��</param>
/// <param name="boomerang">�u�[������</param>
/// <param name="player">�v���C��</param>
BoomerangDrop::BoomerangDrop(BoomerangStateMachine* stateMahine, Boomerang* boomerang)
	:
	m_stateMahine{ stateMahine }
	, m_boomerang{ boomerang }
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoomerangDrop::~BoomerangDrop()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangDrop::Update(const float& deltaTime)
{

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BoomerangDrop::Enter()
{
	//���W�b�g�{�f�B�[�̗L��
	m_boomerang->GetComponent<RigidbodyComponent>()->SetActive(false);
	m_boomerang->GetComponent<PickableComponent>()->SetIsPossible(true);

}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BoomerangDrop::Exit()
{
	m_boomerang->GetComponent<PickableComponent>()->SetIsPossible(false);

}
