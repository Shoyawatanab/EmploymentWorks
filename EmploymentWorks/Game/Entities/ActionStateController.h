/*
* プレイヤクラス　
*/

#pragma once
#include "Game/Interface/IActione.h"


class ActionStateController 
{
public:
	//コンストラク
	ActionStateController();
	//デストラクタ
	~ActionStateController();
	//初期化
	void Initialize(std::vector<IAction*> actions);
	//更新処理
	IAction::ActionState Update(const float& elapsedTime);
	//状態に入った時
	virtual void Enter();
	//状態を抜けた時
	virtual void Exit();
	//状態の切り替え
	void ChangeState();

private:
	//各状態の保存変数
	std::vector<IAction*> m_actionState;
	//添え字
	int m_currentIndex;

};


