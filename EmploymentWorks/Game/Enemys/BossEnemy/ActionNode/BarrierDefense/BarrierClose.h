#pragma once
#include <pch.h>
#include "Game/Interface/IActione.h"

//�O���錾
class CommonResources;
class BarrierDefenseAction;
class Barrier;
class CharacterEntity;

// BarrierClose�N���X���`����
class BarrierClose : public IAction
{
public:

	static constexpr float CLOSE_TIME = 1.0f;

public:
	// �R���X�g���N�^
	BarrierClose(CommonResources* resources,BarrierDefenseAction* barrierDefenseAction, Barrier* barrier, CharacterEntity* owner);
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
	//�o���A�h��̃R���g���[���[
	BarrierDefenseAction* m_barrierDefenseAction;
	//�o���A
	Barrier* m_barrier;
	//����
	float m_time;
	//
	CharacterEntity* m_owner;

};

