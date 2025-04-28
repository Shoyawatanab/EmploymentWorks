#pragma once
#include <pch.h>
#include "Game/Interface/IActione.h"
class CommonResources;
class BarrierDefenseAction;


// BarrierIdelクラスを定義する
class BarrierIdel : public IAction
{
public:
	// コンストラクタ
	BarrierIdel(CommonResources* resources,BarrierDefenseAction* barrierDefenseAction);
	// デストラクタ
	~BarrierIdel();
	//初期化
	void Initialize() override;
	// 更新する
	ActionState Update(const float& elapsedTime);
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;


private:

	// 共通リソース
	CommonResources* m_commonResources;

	BarrierDefenseAction* m_barrierDefenseAction;

};

