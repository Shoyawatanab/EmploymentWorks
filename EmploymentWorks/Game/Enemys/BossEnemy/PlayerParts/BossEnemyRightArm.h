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
class BossEnemyRightArm : public BossEnemyPartsBase
{

private:
	//static constexpr コンパイル時に決定する　クラス外での変更をする必要がないため
	//static cons      クラス外で変更する可能性がある場合

	static constexpr const char PARTSNAME[] = "RightArm";


public:
	//コンストラクタ
	BossEnemyRightArm(CommonResources* resources,
		BossEnemy* root,                         //プレイヤの元もクラス（Player.cpp）
		CharacterEntity* parent, 		                         //親クラス
		DirectX::SimpleMath::Vector3 scale,                  //初期の大きさ
		DirectX::SimpleMath::Vector3 position,               //親の座標からどれだけ離れているか
		DirectX::SimpleMath::Quaternion rotation);           //+Zに向いているときの回転情報
	//デストラクタ
	~BossEnemyRightArm() override;


	//初期化
	void Initialize() override;
	//当たった時に呼び出される
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;

};

