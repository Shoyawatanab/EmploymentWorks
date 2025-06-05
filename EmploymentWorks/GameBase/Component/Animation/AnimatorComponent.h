#pragma once
#include "GameBase/Component.h"

class AnimationController;

class AnimatorComponent : public Component
{
public:
	//�R���X�g���N�^
	AnimatorComponent(Actor* owner, std::unique_ptr<AnimationController> controller);
	//�f�X�g���N�^
	~AnimatorComponent() override ;

	// �A�b�v�f�[�g
	void Update(const float& deltaTime)override;

private:
	//�R���g���[���[
	std::unique_ptr<AnimationController> m_controller;


};