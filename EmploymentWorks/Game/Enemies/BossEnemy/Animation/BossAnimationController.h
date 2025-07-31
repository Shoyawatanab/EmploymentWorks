/*
	�N���X��     : BossAnimationController
	����         : �{�X�G�̃A�j���[�V�����R���g���[���[
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Animation/AnimationController.h"
#include "Game/Messenger/Messengers.h"

class BossEnemy;

class BossAnimationController : public AnimationController 
{
public:
	//�R���X�g���N�^
	BossAnimationController(BossEnemy* bossEnemy);
	//�f�X�g���N�^
	~BossAnimationController() override ;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas)  ;


private:

};