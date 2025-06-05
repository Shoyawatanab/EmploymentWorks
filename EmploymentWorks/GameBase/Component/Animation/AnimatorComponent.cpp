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
/// デストラクタ
/// </summary>
AnimatorComponent::~AnimatorComponent()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void AnimatorComponent::Update(const float& deltaTime)
{
	m_controller->Update(deltaTime);
}

