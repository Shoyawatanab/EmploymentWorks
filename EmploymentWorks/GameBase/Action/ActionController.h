/*
* �v���C���N���X�@
*/

#pragma once
#include "Game/Interface/IActione.h"


class ActionController 
{
public:
	//�R���X�g���N
	ActionController();
	//�f�X�g���N�^
	virtual ~ActionController();
	//�X�V����
	IAction::ActionState Update(const float& elapsedTime);
	//��Ԃɓ�������
	virtual void Enter();
	//��Ԃ𔲂�����
	virtual void Exit();
	//��Ԃ̐؂�ւ�
	void ChangeState();
	//�s���̒ǉ�
	void AddAction(std::vector<IAction*> actions);

private:
	//�e��Ԃ̕ۑ��ϐ�
	std::vector<IAction*> m_actionList;
	//�Y����
	int m_currentIndex;

};


