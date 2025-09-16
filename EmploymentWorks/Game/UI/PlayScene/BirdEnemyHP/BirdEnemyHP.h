/*
	クラス名     : BirdEnemyHP
	説明         : 鳥敵のHPのUI
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"

class Canvas;
class Image;

class BirdEnemyHP : public Actor 
{
public:
	//座標
	static constexpr DirectX::SimpleMath::Vector3 POSITION{4, 5.0, 0};
	//背景の大きさ
	static constexpr DirectX::SimpleMath::Vector3 BACKGRAUND_SCALE{1, 0.9, 1};
	//座標
	static constexpr DirectX::SimpleMath::Vector3 HP_BAR_SCALE{1, 0.85, 1};
public:
	//コンストラクタ
	BirdEnemyHP(Canvas* canvas);
	//デストラクタ
	~BirdEnemyHP() override ;

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas);


private:

	Image* m_backGraund;

	Image* m_hpBar;

};

