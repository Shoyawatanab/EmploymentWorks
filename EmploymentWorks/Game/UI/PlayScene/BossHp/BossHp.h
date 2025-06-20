#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"

class Canvas;
class Image;

class BossHp : public Actor , public IObserver
{
public:
	//�R���X�g���N�^
	BossHp(Canvas* canvas);
	//�f�X�g���N�^
	~BossHp() override ;

	//�ʒm���ɌĂяo�����
	void Notify(MessageType type, void* datas) override;


private:

	Image* m_backGraund;

	Image* m_hpBar;

};

