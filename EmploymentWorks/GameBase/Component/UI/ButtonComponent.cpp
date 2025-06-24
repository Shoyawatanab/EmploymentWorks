#include "pch.h"
#include "ButtonComponent.h"
#include "GameBase/Actor.h"
#include "GameBase/Component/Components.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Manager/UIManager.h"

ButtonComponent::ButtonComponent(Actor* owner)
	:
	Component(owner)
	, m_clickFunction{}
	,m_inRangeFunction{}
	,m_outOfRangeFunction{}
{

	//�}�l�[�W���[�ɒǉ�
	GetActor()->GetScene()->GetUIManager()->AddButtomComponent(this);

}

ButtonComponent::~ButtonComponent()
{
}

/// <summary>
/// �N���b�N��
/// </summary>
void ButtonComponent::OnClick()
{
	//�֐��������
	if (!m_clickFunction)
	{
		return;
	}

	//�o�^�֐��̎��s
	m_clickFunction();

}

/// <summary>
///�@�͈͓��ɂȂ������̏���
/// </summary>
void ButtonComponent::InRange()
{
	//�Ȃ����
	if (!m_inRangeFunction)
	{
		return;
	}
	//�֐����s
	m_inRangeFunction();
}

/// <summary>
/// �͈͊O�ɂȂ������֐�
/// </summary>
void ButtonComponent::OutOfRange()
{
	//�Ȃ����
	if (!m_outOfRangeFunction)
	{
		return;
	}
	//�֐����s
	m_outOfRangeFunction();
}
