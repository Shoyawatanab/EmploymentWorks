#pragma once
#include "GameBase/Animation/AnimationController.h"

class Player2;

class PlayerAnimationController : public AnimationController
{
public:
	//�R���X�g���N�^
	PlayerAnimationController(Player2* player);
	//�f�X�g���N�^
	~PlayerAnimationController() override ;

private:

};