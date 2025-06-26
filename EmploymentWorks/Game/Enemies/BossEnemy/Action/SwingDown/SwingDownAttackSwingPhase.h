/*
	@file	SwingDownAttackSwingPhase.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"
#include "GameBase/Actor.h"

// �O���錾
class CommonResources;
class SwingDownAttackActionController;




class SwingDownAttackSwingPhase : public IAction
{
public:
	//�U�艺�낵����
	static constexpr float SWING_TIME = 3.0f;


public:
	//�R���X�g���N�^
	SwingDownAttackSwingPhase(SwingDownAttackActionController* controller
		, Actor* owner
		);
	//�f�X�g���N�^
	~SwingDownAttackSwingPhase() override ;
	//�X�V����
	ActionState Update(const float& elapsedTime)  override ;
	//��Ԃɓ�������
	void Enter() override ;
	//��Ԃ𔲂�����
	void Exit() override;

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//���L��
	Actor* m_owner;
	//�R���g���[���[
	SwingDownAttackActionController* m_controller;


	float m_time;
	

};
