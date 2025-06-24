#pragma once
#include "GameBase/StateMachine/StateMachine.h"
#include "GameBase/Messenger/IObserver.h"

class BirdEnemy;

enum class BirdEnemyState
{
	IDEL                                  //通常
	,MOVE                                 //動き
	,BEAM_ATTACK						  //ビーム攻撃
};


class BirdEnemyStateMachine : public StateMachine<IState, BirdEnemyState> , public IObserver
{
public:
	//コンストラク
	BirdEnemyStateMachine(BirdEnemy* birdEnemy);
	//デストラクタ
	~BirdEnemyStateMachine() override ;

	//通知時に呼び出される
	void Notify(MessageType type, void* datas) override;


};


