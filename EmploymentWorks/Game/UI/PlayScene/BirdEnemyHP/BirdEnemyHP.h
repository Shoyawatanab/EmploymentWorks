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
	static constexpr DirectX::SimpleMath::Vector3 OFFSET_POSITION{0, 1.0, 0};
	//背景の大きさ
	static constexpr DirectX::SimpleMath::Vector3 BACKGRAUND_SCALE{1, 0.9, 1};
	//座標
	static constexpr DirectX::SimpleMath::Vector3 HP_BAR_SCALE{1, 0.85, 1};

	//アニメーション最大時間
	static constexpr float ANIMATION_MAX_TIME{ 0.2f };

public:

	
	//割合の登録
	void SetRatio(float ration);

public:
	//コンストラクタ
	BirdEnemyHP(Canvas* canvas,Actor* owner);
	//デストラクタ
	~BirdEnemyHP() override ;

	// 単体更新
	void UpdateActor(const float& deltaTime) override;


private:

	//背景
	Image* m_backGraund;
	//HPバー
	Image* m_hpBar;
	//赤色のHPバー
	Image* m_redHpBar;

	//所有者
	Actor* m_owner;

	//現在の割合
	float m_currentRatio;

	//の割合
	float m_startRatio;	
	
	//現在の割合
	float m_endtRatio;

	//アニメーションをするか
	bool m_isAnimation;

	//アニメーション時間
	float m_animationTime;

};

