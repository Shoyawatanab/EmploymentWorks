/*
	クラス名     : PlayerRightArm
	説明         : プレイヤの右腕モデル
	補足・注意点 :
*/
#pragma once
#include "Game/Player/PlayerParts.h"


// 「砲塔」クラスを定義する
class PlayerRightArm : public PlayerParts
{
private :

	//パーツ名
	static constexpr const char PARTS_NAME[] = "RightArm";

public:
	//コンストラクタ
	PlayerRightArm(Scene* scene);
	//デストラクタ
	~PlayerRightArm() override;



};

