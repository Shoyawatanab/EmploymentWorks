/*
* プレイヤの通常状態クラス
*/
#pragma once
#include "Game/Interface/IStateMachine.h"
#include "Game/Interface/IState.h"
#include "Game/Enemys/BossEnemy/Barrier/State/BarrierGenerate.h"
#include "Game/Enemys/BossEnemy/Barrier/State/BarrierShrink.h"


//前方宣言
class Player;

class BarrierStateMachine : public IStateMachine<IState>
{
public:

	//現在の状態の取得
	IState* GetCurrentState() { return m_currentState; }

	BarrierGenerate* GetBarrierGenerare() { return m_generate.get(); }

	BarrierShrink* GetBarrierShrink() { return m_shrink.get(); }

public:
	//コンストラクタ
	BarrierStateMachine(CommonResources* resources
		, Barrier* barrier);
	//デストラクタ
	~BarrierStateMachine() override;

	//初期化
	void Initialize(CommonResources* resources, IState* startState = nullptr);
	// 更新処理
	void Update(const float& elapsedTime) override;
	//状態の変更
	void ChangeState(IState* nextState) override;



private:
	//現在の状態
	IState* m_currentState;
	//バリアの生成
	std::unique_ptr<BarrierGenerate> m_generate;
	//バリアの縮む
	std::unique_ptr<BarrierShrink> m_shrink;

	
};