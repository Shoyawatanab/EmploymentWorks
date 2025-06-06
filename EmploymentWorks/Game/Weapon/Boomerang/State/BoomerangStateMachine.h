/*
* プレイヤの通常状態クラス
*/
#pragma once
#include "Game/Interface/IStateMachine.h"
#include "Game/Interface/IState.h"
#include "Game/Weapon/Boomerang/State/BoomerangIdle.h"
#include "Game/Weapon/Boomerang/State/BoomerangGetReady.h"
#include "Game/Weapon/Boomerang/State/BoomerangRightThrow.h"
#include "Game/Weapon/Boomerang/State/BoomerangLeftThrow.h"
#include "Game/Weapon/Boomerang/State/BoomerangFrontThrow.h"

#include "Game/Weapon/Boomerang/State/BoomerangRepelled.h"
#include "Game/Weapon/Boomerang/State/BoomerangDrop.h"

class TargetMarker;

class BoomerangStateMachine : public IStateMachine<IState>
{
public:

	//現在の状態の取得
	IState* GetCurrentState() { return m_currentState; }
	//通常状態の取得
	BoomerangIdle* GetBoomerangIdel() { return m_idle.get(); }
	//構え状態の取得
	BoomerangGetReady* GetBoomerangGetReady() { return m_getReady.get(); }
	//投げ状態の取得
	BoomerangRightThrow* GetBoomerangRightThrow() { return m_rigntThrow.get(); }

	BoomerangLeftThrow* GetBoomerangLeftThrow() { return m_leftThrow.get(); }

	BoomerangFrontThrow* GetBoomerangFrontThrow() { return m_frontThrow.get(); }

	BoomerangRepelled* GetBoomerangRepelled() { return m_repelled.get(); }

	BoomerangDrop* GetBoomerangDrop() { return m_drop.get(); }

public:
	//コンストラクタ
	BoomerangStateMachine(Boomerang* boomerang) ;
	//デストラクタ
	~BoomerangStateMachine() override;

	//初期化
	void Initialize(CommonResources* resources, IState* startState = nullptr) ;
	// 更新する
	void Update(const float& elapsedTime) override;
	//状態の変更
	void ChangeState(IState* nextState) override;


private:
	//現在の状態
	IState* m_currentState;
	//通常状態
	std::unique_ptr<BoomerangIdle> m_idle;
	//構え状態
	std::unique_ptr<BoomerangGetReady> m_getReady;
	//投げ状態
	std::unique_ptr<BoomerangRightThrow> m_rigntThrow;

	std::unique_ptr<BoomerangLeftThrow> m_leftThrow;

	std::unique_ptr<BoomerangFrontThrow> m_frontThrow;

	std::unique_ptr<BoomerangRepelled> m_repelled;
	
	std::unique_ptr<BoomerangDrop> m_drop;
};