/*
	クラス名     : BossHp
	説明         : ボスHPのUI
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"

class Canvas;
class Image;

class BossHp : public Actor 
{
public:
	//コンストラクタ
	BossHp(Canvas* canvas);
	//デストラクタ
	~BossHp() override ;

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas);


private:

	Image* m_backGraund;

	Image* m_hpBar;

};

