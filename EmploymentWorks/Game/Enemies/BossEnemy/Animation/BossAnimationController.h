#pragma once
#include "GameBase/Animation/AnimationController.h"
#include "GameBase/Messenger/IObserver.h"

class BossEnemy;

class BossAnimationController : public AnimationController , public IObserver
{
public:
	//コンストラクタ
	BossAnimationController(BossEnemy* bossEnemy);
	//デストラクタ
	~BossAnimationController() override ;

	//通知時に呼び出される
	void Notify(MessageType type, void* datas) override ;


private:

};