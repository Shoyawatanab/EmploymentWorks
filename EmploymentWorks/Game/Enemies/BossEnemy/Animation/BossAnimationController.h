#pragma once
#include "GameBase/Animation/AnimationController.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class BossEnemy;

class BossAnimationController : public AnimationController , public IObserver<SceneMessageType>
{
public:
	//�R���X�g���N�^
	BossAnimationController(BossEnemy* bossEnemy);
	//�f�X�g���N�^
	~BossAnimationController() override ;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas) override ;


private:

};