/*
* プレイヤクラス　
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
	//状態に入った時
	virtual void Enter();
	//状態を抜けた時
	virtual void Exit();

	void ChangeState();

private:

	std::vector<IAction*> m_actionState;

	int m_currentIndex;

};


