/*
	�N���X��     : IdleingAction
	����         : �{�X�G�̒ʏ���
	�⑫�E���ӓ_ : 
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
