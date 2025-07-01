#include "pch.h"
#include "EnemyBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
/// <param name="hp">HP</param>
EnemyBase::EnemyBase(Scene* scene, int hp)
	:
	Actor(scene)
	,m_hp{hp}
	,m_model{}
	,m_maxHp{hp}
	,m_manger{}
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyBase::~EnemyBase()
{
}

/// <summary>
/// HP�̌���
/// </summary>
/// <param name="damage">�_���[�W</param>
void EnemyBase::HpDecrease(int damage)
{
	//HP�̌���
	m_hp -= damage;
	//�O�ȉ��ɂȂ�Ȃ��悤��
	m_hp = std::max(m_hp, 0);
}
