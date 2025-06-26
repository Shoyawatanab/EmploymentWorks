#pragma once
#include "GameBase/Animation/AnimationController.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class Player;

class PlayerAnimationController : public AnimationController , public IObserver<SceneMessageType>
{
public:
	//�R���X�g���N�^
	PlayerAnimationController(Player* player);
	//�f�X�g���N�^
	~PlayerAnimationController() override ;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas) override ;


private:

};