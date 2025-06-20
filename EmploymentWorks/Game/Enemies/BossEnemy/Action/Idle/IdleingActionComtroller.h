/*
	@file	IdleingActionComtroller.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "GameBase/Action/ActionController.h"

class IdleingAction;


class IdleingActionComtroller : public ActionController
{
public:
	//コンストラク
	IdleingActionComtroller();
	//デストラクタ
	~IdleingActionComtroller()override;

private:
	std::unique_ptr<IdleingAction> m_idle;

};
