#pragma once
#include "GameBase/StateMachine/StateMachine.h"
#include "GameBase/Messenger/IObserver.h"


class BirdEnemyBullet;
class BirdEnemy;

enum class BirdEnemyBulletState
{
	IDEL                                  //通常
	,CHAGE                                //チャージ
	,SHOT						          //ショット
};


class BirdEnemyBulletStateMachine : public StateMachine<IState, BirdEnemyBulletState> , public IObserver
{
public:
	//コンストラク
	BirdEnemyBulletStateMachine(BirdEnemyBullet* bullet, BirdEnemy* birdEnemy);
	//デストラクタ
	~BirdEnemyBulletStateMachine() override ;

	//通知時に呼び出される
	void Notify(MessageType type, void* datas) override;


};


