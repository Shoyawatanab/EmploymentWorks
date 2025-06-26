/*
	@file	IdleingAction.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"



class IdleingAction : public IAction
{
public:
	//�R���X�g���N�^
	IdleingAction();
	//�f�X�g���N�^
	~IdleingAction() override ;
	//�X�V����
	ActionState Update(const float& elapsedTime)  override ;
	//��Ԃɓ�������
	void Enter() override ;
	//��Ԃ𔲂�����
	void Exit() override;

};
