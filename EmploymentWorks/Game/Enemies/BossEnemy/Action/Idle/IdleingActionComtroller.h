/*
	@file	IdleingActionComtroller.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "GameBase/Action/ActionController.h"

class IdleingAction;


class IdleingActionComtroller : public ActionController
{
public:
	//�R���X�g���N
	IdleingActionComtroller();
	//�f�X�g���N�^
	~IdleingActionComtroller()override;

private:
	//�ʏ�
	std::unique_ptr<IdleingAction> m_idle;

};
