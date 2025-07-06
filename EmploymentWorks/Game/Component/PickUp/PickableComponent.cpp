#include "pch.h"
#include "PickableComponent.h"
#include "Game/Manager/PickUp/PickUpManager.h"
#include "Game/Scene/PlayScene.h"


/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="owner">���L��</param>
/// <param name="type">����^�C�v</param>
PickableComponent ::PickableComponent (Actor* owner, PickUpManager::PickUpType type)
	:
	Component(owner)
	,m_isPossible{false}
{

	//���݂̃V�[�����v���C�V�[���ɃL���X�g
	auto playScene = static_cast<PlayScene*>(GetActor()->GetScene());
	//�v���C�V�[���̃}�l�[�W���[�ɏE���鑤�Ƃ��ēo�^
	playScene->GetPickUpManager()->AddPickable(type, this);


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PickableComponent ::~PickableComponent ()
{
}

/// <summary>
/// �����
/// </summary>
void PickableComponent::OnPickUp()
{
	//�o�^����Ă��Ȃ����
	if (!m_onPickUp)
	{
		return;
	}

	//�֐����s
	m_onPickUp();

}

/// <summary>
/// ����ł���悤�ɂȂ����Ƃ�
/// </summary>
void PickableComponent::OnRecoverable()
{

	//�Ȃ����
	if(!m_recoverable)
	{
		return;
	}

	//�֐����s
	m_recoverable();

}

/// <summary>
/// ����ł��Ȃ��Ȃ����Ƃ�
/// </summary>
void PickableComponent::OnUnrecoverable()
{

	//�Ȃ����
	if (!m_unrecoverable)
	{
		return;
	}

	//�֐����s
	m_unrecoverable;

}
