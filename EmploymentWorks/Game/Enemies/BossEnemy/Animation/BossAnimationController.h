#pragma once
#include "GameBase/Animation/AnimationController.h"
#include "GameBase/Messenger/IObserver.h"

class BossEnemy;

class BossAnimationController : public AnimationController , public IObserver
{
public:
	//�R���X�g���N�^
	BossAnimationController(BossEnemy* bossEnemy);
	//�f�X�g���N�^
	~BossAnimationController() override ;

	//�ʒm���ɌĂяo�����
	void Notify(MessageType type, void* datas) override ;


private:

};