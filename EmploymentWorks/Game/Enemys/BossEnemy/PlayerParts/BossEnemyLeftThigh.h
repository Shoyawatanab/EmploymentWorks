/*
* プレイヤの体クラス
*/

#pragma once
#include "Game/Enemys/BossEnemy/BossEnemyPartsBase.h"


//前方宣言
class Enemy;

namespace WataLib
{
	class Animation;
	class Bounding;

}

// 「砲塔」クラスを定義する
class BossEnemyLeftThigh : public BossEnemyPartsBase
{

private:

	//パーツ名
	static constexpr const char PARTSNAME[] = "LeftThigh";

public:
	//コンストラクタ
	BossEnemyLeftThigh(CommonResources* resources,
		BossEnemy* root,                         //プレイヤの元もクラス（Player.cpp）
		CharacterEntity* parent, 		                         //親クラス
		DirectX::SimpleMath::Vector3 scale,                  //初期の大きさ
		DirectX::SimpleMath::Vector3 position,               //親の座標からどれだけ離れているか
		DirectX::SimpleMath::Quaternion rotation);           //+Zに向いているときの回転情報
	//デストラクタ
	~BossEnemyLeftThigh() override;


	//IObject
	//初期化
	void Initialize() override;

};

