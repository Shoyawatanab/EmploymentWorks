#include"pch.h"
#include"Actor.h"
#include"Component.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="actor">�����A�N�^�[</param>
/// <param name="updateOrder">�A�b�v�f�[�g�x���p</param>
Component::Component(Actor* actor, int updateOrder)
	:
	m_actor{actor},
	m_isActive{true},
	m_updateOrder{updateOrder},
	m_isDestroy{false}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Component::~Component()
{

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void Component::Update(const float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/// <summary>
/// �j�󂷂�
/// </summary>
void Component::Destroy()
{
	// �A�N�^�[�̔j�󏈗����I���ɂ���
	GetActor()->ComponentDestroyOn();
	// ���S�t���O�ݒ�
	m_isDestroy = true;
	// �A�N�e�B�u�t���O�ݒ�
	SetActive(false);
}


