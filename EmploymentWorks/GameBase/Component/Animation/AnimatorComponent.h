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
	//�A�j���[�V�����̍Đ�
	void Play(const std::string& animatioName);

	//1��A�j���[�V�������s
	void SetTrigger(const std::string& connectionName);

	//�A�j���[�V�����̐؂�ւ��@�΂����傫���ꍇ�̂ݕύX
	void SetFloat(const std::string& connectionName, const float& value);



private:
	//�R���g���[���[
	std::unique_ptr<AnimationController> m_controller;


};