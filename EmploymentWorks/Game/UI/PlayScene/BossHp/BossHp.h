/*
	�N���X��     : BossHp
	����         : �{�XHP��UI
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"

class Canvas;
class Image;

class BossHp : public Actor 
{
public:
	//�R���X�g���N�^
	BossHp(Canvas* canvas);
	//�f�X�g���N�^
	~BossHp() override ;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas);


private:

	Image* m_backGraund;

	Image* m_hpBar;

};

