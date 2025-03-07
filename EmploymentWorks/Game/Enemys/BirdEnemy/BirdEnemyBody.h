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
	static constexpr const char PARTSNAME[] = "Body";


public:

	BirdEnemyBody(CommonResources* resources,
		CharacterEntity* parent, 		                         //親クラス
		DirectX::SimpleMath::Vector3 scale,                  //初期の大きさ
		DirectX::SimpleMath::Vector3 position,               //親の座標からどれだけ離れているか
		DirectX::SimpleMath::Quaternion rotation);           //+Zに向いているときの回転情報


	~BirdEnemyBody() override ;

	//IObject
	//初期化
	void Initialize() override;

	void Update(const float& elapsedTime) override;


};
