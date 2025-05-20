#pragma once
#include <pch.h>
#include "Game/Interface/IActione.h"
//�O���錾
class CommonResources;
class BarrierDefenseAction;
class Barrier;

// BarrierDeployment�N���X���`����
class BarrierDeployment : public IAction
{
public:
	//�W�J����
	static constexpr float DEPLOYMENT_TIME = 5.0f;

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
	//�R���g���[���[
	BarrierDefenseAction* m_barrierDefenseAction;
	//�o���A
	Barrier* m_barrier;
	//����
	float m_time;

};

