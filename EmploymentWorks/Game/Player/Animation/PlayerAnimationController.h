#pragma once
#include "GameBase/Animation/AnimationController.h"

class Player2;

class PlayerAnimationController : public AnimationController
{
public:
	//コンストラクタ
	PlayerAnimationController(Player2* player);
	//デストラクタ
	~PlayerAnimationController() override ;

private:

};