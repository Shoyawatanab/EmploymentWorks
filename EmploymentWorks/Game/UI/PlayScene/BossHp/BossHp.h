#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class Canvas;
class Image;

class BossHp : public Actor , public IObserver<SceneMessageType>
{
public:
	//�R���X�g���N�^
	BossHp(Canvas* canvas);
	//�f�X�g���N�^
	~BossHp() override ;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas) override;


private:

	Image* m_backGraund;

	Image* m_hpBar;

};

