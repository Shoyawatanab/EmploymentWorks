/*
* 鳥の敵のビームのステートマシン
*/
#pragma once
#include "Game/Interface/IStateMachine.h"
#include "Game/Interface/IState.h"
#include "Game/Enemys/BirdEnemy/Beam/BeamState/BirdEnemyBeamIdling.h"
#include "Game/Enemys/BirdEnemy/Beam/BeamState/BirdEnemyBeamPreliminaryAction.h"
#include "Game/Enemys/BirdEnemy/Beam/BeamState/BirdEnemyBeamAttack.h"


class Player;
class BirdEnemy;

class BirdEnemyBeamStateMachine : public IStateMachine
{
public:
	//現在の状態の取得
	IState* GetCurrentState() { return m_currentState; }

	BirdEnemyBeamIdling* GetBirdEnemyBeamIdle() { return m_idle.get(); }

	BirdEnemyBeamAttack* GetBirdEnemyBeamAttack() { return m_attack.get(); }

	BirdEnemyBeamPreliminaryAction* GetBirdEnemyBeamPreliminaryAction() { return m_preliminaryAction.get(); }

public:
	//コンストラクタ
	BirdEnemyBeamStateMachine(Player* player, BirdEnemy* enemy, BirdEnemyBeam* beam);
	//デストラクタ
	~BirdEnemyBeamStateMachine() override;

	//初期化
	void Initialize(CommonResources* resources, IState* startState = nullptr) override;
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
	std::unique_ptr<BirdEnemyBeamIdling> m_idle;
	//攻撃
	std::unique_ptr<BirdEnemyBeamAttack> m_attack;
	//予備動作
	std::unique_ptr<BirdEnemyBeamPreliminaryAction> m_preliminaryAction;


	
};