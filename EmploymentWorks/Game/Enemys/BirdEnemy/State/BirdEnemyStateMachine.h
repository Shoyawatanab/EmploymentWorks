/*
* 鳥の敵のステートマシン
*/
#pragma once
#include "Game/Interface/IStateMachine.h"
#include "Game/Interface/IState.h"
#include "Game/Enemys/BirdEnemy/State/BirdEnemyIdling.h"
#include "Game/Enemys/BirdEnemy/State/BirdEnemyAttack.h"
#include "Game/Enemys/BirdEnemy/State/BirdEnemyMove.h"

//前方宣言
class Player;
class BirdEnemy;

class BirdEnemyStateMachine : public IStateMachine
{
public:

	//現在の状態の取得
	IState* GetCurrentState() { return m_currentState; }

	BirdEnemyldling* GetBirdEnemyldling() { return m_idle.get(); }

	BirdEnemyAttack* GetBirdEnemyAttack() { return m_attack.get(); }

	BirdEnemyMove* GetBirdEnemyMove() { return m_move.get(); }

public:
	//コンストラクタ
	BirdEnemyStateMachine();
	//デストラクタ
	~BirdEnemyStateMachine() override;
	//初期化
	void Initialize(CommonResources* resources, BirdEnemy* owner);
	// 更新処理
	void Update(const float& elapsedTime) override;
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//状態の変更
	void ChangeState(IState* nextState) override;


private:
	//現在の状態
	IState* m_currentState;
	//通常状態
	std::unique_ptr<BirdEnemyldling> m_idle;
	//攻撃
	std::unique_ptr<BirdEnemyAttack> m_attack;
	std::unique_ptr<BirdEnemyMove> m_move;


	
};