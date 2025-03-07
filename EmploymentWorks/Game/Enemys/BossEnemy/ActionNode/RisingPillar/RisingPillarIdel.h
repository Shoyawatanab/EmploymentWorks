#pragma once
#include <pch.h>
#include "Game/Interface/IActionState.h"
class CommonResources;
class RisingPillarvAction;


// RisingPillarIdel�N���X���`����
class RisingPillarIdel : public IActionState
{
public:
	// �R���X�g���N�^
	RisingPillarIdel(RisingPillarvAction* risingPillarvAction);
	// �f�X�g���N�^
	~RisingPillarIdel();
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

	RisingPillarvAction* m_risingPillarvAction;

};

