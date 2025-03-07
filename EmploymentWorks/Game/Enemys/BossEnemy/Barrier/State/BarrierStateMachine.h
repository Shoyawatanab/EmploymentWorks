/*
* プレイヤの通常状態クラス
*/
#pragma once
#include "Game/Interface/IStateMachine.h"
#include "Game/Interface/IState.h"
#include "Game/Enemys/BossEnemy/Barrier/State/BarrierGenerate.h"
#include "Game/Enemys/BossEnemy/Barrier/State/BarrierShrink.h"



class Player;

class BarrierStateMachine : public IStateMachine
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
	void Initialize(CommonResources* resources, IState* startState = nullptr) override;
	// 更新する
	void Update(const float& elapsedTime) override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//状態の変更
	void ChangeState(IState* nextState) override;

	//必要なポインタの登録
	void AddPointer(Player* player);


private:
	//現在の状態
	IState* m_currentState;

	std::unique_ptr<BarrierGenerate> m_generate;

	std::unique_ptr<BarrierShrink> m_shrink;

	
};