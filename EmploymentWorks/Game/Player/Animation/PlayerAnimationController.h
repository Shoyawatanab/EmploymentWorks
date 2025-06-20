#pragma once
#include "GameBase/Animation/AnimationController.h"
#include "GameBase/Messenger/IObserver.h"

class Player;

class PlayerAnimationController : public AnimationController , public IObserver
{
public:
	//�R���X�g���N�^
	PlayerAnimationController(Player* player);
	//�f�X�g���N�^
	~PlayerAnimationController() override ;

	//�ʒm���ɌĂяo�����
	void Notify(MessageType type, void* datas) override ;


private:

};