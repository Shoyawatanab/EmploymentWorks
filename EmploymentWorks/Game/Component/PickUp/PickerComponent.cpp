/*
	�N���X��    : PickerComponent
	����        : �E�����R���|�[�l���g
	�⑫�E���ӓ_:�@���̃Q�[���I���W�i���R���|�[�l���g
	�@�@�@�@�@�@�@�v���C�V�[���Ƀ}�l�[�W���[������
*/
#include "pch.h"
#include "PickerComponent.h"
#include "Game/Manager/PickUp/PickUpManager.h"
#include "Game/Scene/PlayScene.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="owner">���L��</param>
/// <param name="type">����^�C�v</param>
/// <param name="pickUpRadius">����͈�</param>
PickerComponent::PickerComponent(Actor* owner, PickUpManager::PickUpType type, float pickUpRadius)
	:
	Component(owner)
	,m_pickUpRadius{pickUpRadius}
	,m_isPickUp{false}
	,m_isRecoverable{false}
	,m_type{type}
{

	//���݂̃V�[�����v���C�V�[���ɃL���X�g
	auto playScene = static_cast<PlayScene*>(GetActor()->GetScene());
	
	//�v���C�V�[������}�l�[�W���[�̎擾
	m_manger = playScene->GetPickUpManager();
	m_manger->AddPicker(type, this);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PickerComponent::~PickerComponent()
{

}

/// <summary>
/// ����̎��s
/// </summary>
void PickerComponent::TryPickUp()
{
	m_manger->TryPickUp(this);
}

/// <summary>
/// �����
/// </summary>
void PickerComponent::OnPickUp()
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
void PickerComponent::OnRecoverable()
{
	//�Ȃ����
	if (!m_recoverable)
	{
		return;
	}

	//�֐����s
	m_recoverable();
}

/// <summary>
/// ����ł��Ȃ��Ȃ����Ƃ�
/// </summary>
void PickerComponent::OnUnrecoverable()
{
	//�Ȃ����
	if (!m_unrecoverable)
	{
		return;
	}

	//�֐����s
	m_unrecoverable();
}
