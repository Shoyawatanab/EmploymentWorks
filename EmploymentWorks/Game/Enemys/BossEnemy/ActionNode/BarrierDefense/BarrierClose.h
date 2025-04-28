#pragma once
#include <pch.h>
#include "Game/Interface/IActione.h"
class CommonResources;
class BarrierDefenseAction;
class Barrier;
class BossEnemy;

// BarrierClose�N���X���`����
class BarrierClose : public IAction
{
public:
	// �R���X�g���N�^
	BarrierClose(CommonResources* resources,BarrierDefenseAction* barrierDefenseAction, Barrier* barrier, BossEnemy* bossEnemy);
	// �f�X�g���N�^
	~BarrierClose();
	//������
	void Initialize() override;
	// �X�V����
	ActionState Update(const float& elapsedTime);
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;


private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	BarrierDefenseAction* m_barrierDefenseAction;

	Barrier* m_barrier;

	float m_time;

	BossEnemy* m_bossEnemy;

};

