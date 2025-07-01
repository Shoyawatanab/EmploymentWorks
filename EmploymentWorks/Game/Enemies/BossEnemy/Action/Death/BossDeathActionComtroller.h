/*
	@file	BossDeathActionComtroller.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "GameBase/Action/ActionController.h"

class BossDeathAction;
class BossDeathEndAction;

class BossEnemy;


class BossDeathActionComtroller : public ActionController
{
public:
	//�R���X�g���N
	BossDeathActionComtroller(BossEnemy* bossEnemy);
	//�f�X�g���N�^
	~BossDeathActionComtroller()override;

private:
	//�ʏ�
	std::unique_ptr<BossDeathAction> m_idle;
	//�I��
	std::unique_ptr<BossDeathEndAction> m_end;
};
