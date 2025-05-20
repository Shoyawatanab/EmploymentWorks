/*
* �v���C���N���X�@
*/

#pragma once
#include "Game/Interface/IActione.h"


class ActionStateController 
{
public:
	//�R���X�g���N
	ActionStateController();
	//�f�X�g���N�^
	~ActionStateController();
	//������
	void Initialize(std::vector<IAction*> actions);
	//�X�V����
	IAction::ActionState Update(const float& elapsedTime);
	//��Ԃɓ�������
	virtual void Enter();
	//��Ԃ𔲂�����
	virtual void Exit();
	//��Ԃ̐؂�ւ�
	void ChangeState();

private:
	//�e��Ԃ̕ۑ��ϐ�
	std::vector<IAction*> m_actionState;
	//�Y����
	int m_currentIndex;

};


