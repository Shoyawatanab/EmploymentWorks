#pragma once
#include <pch.h>
#include "Game/Interface/IActione.h"
class CommonResources;
class BarrierDefenseAction;
class Barrier;

// BarrierDeployment�N���X���`����
class BarrierDeployment : public IAction
{
public:
	// �R���X�g���N�^
	BarrierDeployment(CommonResources* resources,BarrierDefenseAction* barrierDefenseAction, Barrier* barrier);
	// �f�X�g���N�^
	~BarrierDeployment();
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

};

