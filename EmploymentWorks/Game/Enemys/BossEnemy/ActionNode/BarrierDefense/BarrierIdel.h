#pragma once
#include <pch.h>
#include "Game/Interface/IActione.h"
class CommonResources;
class BarrierDefenseAction;


// BarrierIdel�N���X���`����
class BarrierIdel : public IAction
{
public:
	// �R���X�g���N�^
	BarrierIdel(CommonResources* resources,BarrierDefenseAction* barrierDefenseAction);
	// �f�X�g���N�^
	~BarrierIdel();
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

};

