/*
* �v���C���N���X�@
*/

#pragma once
#include "Game/Interface/IActione.h"


class ActionStateController 
{
public:

	ActionStateController();

	~ActionStateController();

	void Initialize(std::vector<IAction*> actions);

	IAction::ActionState Update(const float& elapsedTime);
	//��Ԃɓ�������
	virtual void Enter();
	//��Ԃ𔲂�����
	virtual void Exit();

	void ChangeState();

private:

	std::vector<IAction*> m_actionState;

	int m_currentIndex;

};


