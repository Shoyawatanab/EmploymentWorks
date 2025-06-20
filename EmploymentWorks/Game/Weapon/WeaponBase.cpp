#include "pch.h"
#include "WeaponBase.h"

WeaponBase::WeaponBase(Scene* scene)
	:
	Actor(scene)
	,m_state{WeaponState::BOOMERANG_IDLE}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
WeaponBase::~WeaponBase()
{
}

/// <summary>
/// �X�e�[�g�̕ύX
/// </summary>
/// <param name="nextState">���̃X�e�[�g</param>
void WeaponBase::ChangeState(WeaponState nextState)
{
	//�ʂ̃X�e�[�g�ύX
	ActorChangeState(nextState);

	//��Ԃ̕ύX
	m_state = nextState;
	
}
