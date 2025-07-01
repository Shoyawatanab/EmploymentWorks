#pragma once
#include "Game/Interface/IActione.h"



class BossDeathAction : public IAction
{
public:

	//���ԁ@�A�j���[�V�����ɂ��킹��
	static constexpr float DEATH_TIME = 3.0f;

public:
	//�R���X�g���N�^
	BossDeathAction();
	//�f�X�g���N�^
	~BossDeathAction() override ;
	//�X�V����
	ActionState Update(const float& elapsedTime)  override ;
	//��Ԃɓ�������
	void Enter() override ;
	//��Ԃ𔲂�����
	void Exit() override;

private:
	//����
	float m_time;

};
