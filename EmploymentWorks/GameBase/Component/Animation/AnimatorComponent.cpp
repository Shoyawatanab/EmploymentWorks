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

