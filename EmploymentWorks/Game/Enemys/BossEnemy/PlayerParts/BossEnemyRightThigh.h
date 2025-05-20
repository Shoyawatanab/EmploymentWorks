/*
* プレイヤの体クラス
*/

#pragma once
#include "Game/Enemys/BossEnemy/BossEnemyPartsBase.h"


//前方宣言
namespace WataLib
{
	class Animation;
	class Bounding;

}

// 「砲塔」クラスを定義する
class BossEnemyRightThigh : public BossEnemyPartsBase
{

private:
	//パーティクルの生成のメッセージを送る
	static constexpr const char PARTSNAME[] = "RightThigh";


public:
	//コンストラクタ
	BossEnemyRightThigh(CommonResources* resources,
		BossEnemy* root,                         //プレイヤの元もクラス（Player.cpp）
		CharacterEntity* parent, 		                         //親クラス
		DirectX::SimpleMath::Vector3 scale,                  //初期の大きさ
		DirectX::SimpleMath::Vector3 position,               //親の座標からどれだけ離れているか
		DirectX::SimpleMath::Quaternion rotation);           //+Zに向いているときの回転情報
	//デストラクタ
	~BossEnemyRightThigh() override;

	//初期化
	void Initialize() override;

};

