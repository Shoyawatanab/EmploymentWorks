#pragma once
#include <pch.h>
#include "Game/Interface/IActione.h"
//前方宣言
class CommonResources;
class BarrierDefenseAction;
class Barrier;

// BarrierDeploymentクラスを定義する
class BarrierDeployment : public IAction
{
public:
	//展開時間
	static constexpr float DEPLOYMENT_TIME = 5.0f;

public:
	// コンストラクタ
	BarrierDeployment(CommonResources* resources,BarrierDefenseAction* barrierDefenseAction, Barrier* barrier);
	// デストラクタ
	~BarrierDeployment();
	//初期化
	void Initialize() override;
	// 更新処理
	ActionState Update(const float& elapsedTime);
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;


private:

	// 共通リソース
	CommonResources* m_commonResources;
	//コントローラー
	BarrierDefenseAction* m_barrierDefenseAction;
	//バリア
	Barrier* m_barrier;
	//時間
	float m_time;

};

