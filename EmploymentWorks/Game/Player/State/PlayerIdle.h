/*
* プレイヤの通常状態クラス
*/
#pragma once
#include "Game/Interface/IState.h"

class PlayerStateMachine;
class Player2;

class PlayerIdle : public IState 
{
public:
	//コンストラクタ
	PlayerIdle(PlayerStateMachine* stateMachine,Player2* player) ;
	//デストラクタ
	~PlayerIdle() override;

	// 更新する
	void Update(const float& elapsedTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;


private:
	//プレイヤ
	Player2* m_player;

	PlayerStateMachine* m_stateMahine;
	
};