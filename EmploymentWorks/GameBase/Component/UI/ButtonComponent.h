#pragma once
#include "GameBase/Component.h"


class ButtonComponent : public Component
{
public:
	//�N���b�N���̊֐��̓o�^�@
	void SetClickFunction(std::function<void()> function) { m_clickFunction = function; };
	//�͈͂ɓ��������֐�
	void SetInRangeFunction(std::function<void()> function) { m_inRangeFunction = function; };
	//�͈͊O�ɂȂ������֐�
	void SetOutOfRangeFunction(std::function<void()> function) { m_outOfRangeFunction = function; };

public:
	//�R���X�g���N
	ButtonComponent(Actor* owner);
	//�f�X�g���N�^
	~ButtonComponent();
	
	//�N���b�N��
	void OnClick();
	//�͈͓��ɂȂ������̏���
	void InRange();
	//�͈͊O�ɂȂ������̏���
	void OutOfRange();

private:
	//�N���b�N���֐�
	std::function<void()> m_clickFunction;

	//�͈͂ɓ��������֐�
	std::function<void()> m_inRangeFunction;

	//�͈͊O�ɂȂ������֐�
	std::function<void()> m_outOfRangeFunction;

};