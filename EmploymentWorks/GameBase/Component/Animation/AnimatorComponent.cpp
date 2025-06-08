#include "pch.h"
#include "AnimatorComponent.h"
#include "GameBase/Animation/AnimationController.h"


AnimatorComponent::AnimatorComponent(Actor* owner, std::unique_ptr<AnimationController> controller)
	:
	Component(owner)
	,m_controller{std::move(controller)}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
AnimatorComponent::~AnimatorComponent()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void AnimatorComponent::Update(const float& deltaTime)
{
	m_controller->Update(deltaTime);
}

/// <summary>
/// �A�j���[�V�����̍Đ�
/// </summary>
/// <param name="animatioName">�A�j���[�V������</param>
void AnimatorComponent::Play(const std::string& animatioName)
{
	m_controller->Play(animatioName);
}


/// <summary>
/// �A�j���[�V������1����s
/// </summary>
/// <param name="connectionName">��Ԑڑ���</param>
void AnimatorComponent::SetTrigger(const std::string& connectionName)
{
	m_controller->SetTrigger(connectionName);
}

/// <summary>
/// �l���ݒ�l�����傫����΃A�j���[�V�������Đ�
/// </summary>
/// <param name="connectionName">��Ԑڑ�����</param>
/// <param name="value">�l</param>
void AnimatorComponent::SetFloat(const std::string& connectionName, const float& value)
{
	m_controller->SetFloat(connectionName, value);
}



