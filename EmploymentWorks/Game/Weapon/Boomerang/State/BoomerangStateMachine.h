#pragma once
#include "GameBase/StateMachine/StateMachine.h"

class Boomerang;
class Player;

enum class BoomerangState
{
	IDEL
	,THROW
	,GET_READY
};

class BoomerangStateMachine : public StateMachine<IState, BoomerangState>
{

public:
	//コンストラクタ
	BoomerangStateMachine(Boomerang* boomrang, Player* player);
	//デストラクタ
	~BoomerangStateMachine();



};
