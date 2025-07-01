#pragma once
#include "Game/Interface/IActione.h"

class BossEnemy;


class BossDeathEndAction : public IAction
{
public:

	//���ԁ@�A�j���[�V�����ɂ��킹��
	static constexpr float DEATH_TIME = 3.0f;

public:
	//�R���X�g���N�^
	BossDeathEndAction(BossEnemy* bossEnemy);
	//�f�X�g���N�^
	~BossDeathEndAction() override;
	//�X�V����
	ActionState Update(const float& elapsedTime)  override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;

private:

	//���L��
	BossEnemy* m_bossEnemy;

};
#pragma once
