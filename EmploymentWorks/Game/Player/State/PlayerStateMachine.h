/*
* プレイヤの通常状態クラス
*/
#pragma once

#include "GameBase/StateMachine/StateMachine.h"

class Player2;


enum class PlayerState
{
	IDEL
	, ATTACK
	,WALK
};

class PlayerStateMachine : public StateMachine<IState,PlayerState>//, public IObserver<PlayerMessageType>
{

public:
	//コンストラクタ
	PlayerStateMachine(Player2* player);
	//デストラクタ
	~PlayerStateMachine();



	//void Notify(const Telegram<PlayerMessageType>& telegram)  override;

	
};