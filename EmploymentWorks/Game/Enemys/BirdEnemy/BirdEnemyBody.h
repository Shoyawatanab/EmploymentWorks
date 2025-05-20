/*
	@file	BirdEnemyBody.h
	@brief	鳥の敵の体
*/
#pragma once
#include "Game/Enemys/BirdEnemy/BirdEnemyPartsBase.h"

// 前方宣言
namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BirdEnemyBody : public BirdEnemyPartsBase
{

public:
	//パーツ名
	static constexpr const char PARTSNAME[] = "Body";


public:
	//コンストラクタ
	BirdEnemyBody(CommonResources* resources,
		CharacterEntity* parent, 		                         //親クラス
		DirectX::SimpleMath::Vector3 scale,                  //初期の大きさ
		DirectX::SimpleMath::Vector3 position,               //親の座標からどれだけ離れているか
		DirectX::SimpleMath::Quaternion rotation);           //+Zに向いているときの回転情報

	//デストラクタ
	~BirdEnemyBody() override ;

	//初期化
	void Initialize() override;
	//更新処理
	void Update(const float& elapsedTime) override;


};
