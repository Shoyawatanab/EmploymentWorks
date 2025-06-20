#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"

class Canvas;
class Image;

class BossHp : public Actor , public IObserver
{
public:
	//コンストラクタ
	BossHp(Canvas* canvas);
	//デストラクタ
	~BossHp() override ;

	//通知時に呼び出される
	void Notify(MessageType type, void* datas) override;


private:

	Image* m_backGraund;

	Image* m_hpBar;

};

