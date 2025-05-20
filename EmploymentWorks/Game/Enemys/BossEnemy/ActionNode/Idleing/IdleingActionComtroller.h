/*
	@file	IdleingActionComtroller.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Entities/ActionStateController.h"
#include "Game/Enemys/BossEnemy/ActionNode/Idleing/IdleingAction.h"

// 前方宣言
class CommonResources;
class CharacterEntity;




class IdleingActionComtroller : public ActionStateController
{

public:


public:
	//コンストラク
	IdleingActionComtroller(CommonResources* resources,
		CharacterEntity* own
		);
	//デストラクタ
	~IdleingActionComtroller();

private:
	// 共通リソース
	CommonResources* m_commonResources;
	//所有者
	CharacterEntity* m_own;
	//通常状態
	std::unique_ptr<IdleingAction> m_idle;
};
