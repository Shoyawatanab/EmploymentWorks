/*
	�N���X��     : IdleingAction
	����         : �{�X�G�̒ʏ�̃R���g���[���[
	�⑫�E���ӓ_ :
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
