#pragma once
#include "GameBase/Animation/AnimationController.h"
#include "GameBase/Messenger/IObserver.h"

class Player;

class PlayerAnimationController : public AnimationController , public IObserver
{
public:
	//コンストラクタ
	PlayerAnimationController(Player* player);
	//デストラクタ
	~PlayerAnimationController() override ;

	//通知時に呼び出される
	void Notify(MessageType type, void* datas) override ;


private:

};