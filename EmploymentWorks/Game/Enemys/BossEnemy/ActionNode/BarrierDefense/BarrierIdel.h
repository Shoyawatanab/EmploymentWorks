#pragma once
#include <pch.h>
#include "Game/Interface/IActionState.h"
class CommonResources;
class BarrierDefenseAction;


// BarrierIdel�N���X���`����
class BarrierIdel : public IActionState
{
public:
	// �R���X�g���N�^
	BarrierIdel(BarrierDefenseAction* barrierDefenseAction);
	// �f�X�g���N�^
	~BarrierIdel();
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

};

