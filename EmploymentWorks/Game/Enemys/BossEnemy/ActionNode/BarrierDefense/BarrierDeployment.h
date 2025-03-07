#pragma once
#include <pch.h>
#include "Game/Interface/IActionState.h"
class CommonResources;
class BarrierDefenseAction;
class Barrier;

// BarrierDeployment�N���X���`����
class BarrierDeployment : public IActionState
{
public:
	// �R���X�g���N�^
	BarrierDeployment(BarrierDefenseAction* barrierDefenseAction, Barrier* barrier);
	// �f�X�g���N�^
	~BarrierDeployment();
	//������
	void Initialize(CommonResources* resources) override;
	// �X�V����
	IBehaviorNode::State Update(const float& elapsedTime);
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

