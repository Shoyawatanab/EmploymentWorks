/*
	�N���X��     : PlayerAnimationController
	����         : �v���C���A�j���[�V�����R���g���[���[
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Animation/AnimationController.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class Player;

class PlayerAnimationController : public AnimationController
{
public:
	//�R���X�g���N�^
	PlayerAnimationController(Player* player);
	//�f�X�g���N�^
	~PlayerAnimationController() override ;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas);


private:

};