/*
* プレイヤの通常状態クラス
*/
#pragma once
#include "Game/Interface/IStateMachine.h"
#include "Game/Interface/IState.h"
#include "Game/Player/State/PlayerIdle.h"
#include "Game/Player/State/PlayerAttack.h"


class Player;

class PlayerStateMachine : public IStateMachine
{
public:

	//現在の状態の取得
	IState* GetCurrentState() { return m_currentState; }

	PlayerIdle* GetPlayerIdle() { return m_idle.get(); }

	PlayerAttack* GetPlayerAttack() { return m_attack.get(); }

public:
	//コンストラクタ
	PlayerStateMachine(Player* player);
	//デストラクタ
	~PlayerStateMachine() override;

	//初期化
	void Initialize(CommonResources* resources, IState* startState = nullptr) ;
	// 更新する
	void Update(const float& elapsedTime) override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//状態の変更
	void ChangeState(IState* nextState) override;


private:
	//現在の状態
	IState* m_currentState;
	//通常状態
	std::unique_ptr<PlayerIdle> m_idle;
	//攻撃
	std::unique_ptr<PlayerAttack> m_attack;


	
};