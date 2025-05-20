/*
	@file	BirdEnemyFeather.h
	@brief　鳥の敵の羽
*/
#pragma once
#include "Game/Enemys/BirdEnemy/BirdEnemyPartsBase.h"

//前方宣言
namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BirdEnemyFeather : public BirdEnemyPartsBase
{
public:
	//パーツ名
	static constexpr const char PARTSNAME[] = "Body";

public:
	//羽の状態
	enum class State
	{
		UP
		,DOWN
	};


public:
	//コンストラクタ
	BirdEnemyFeather(CommonResources* resources, 
		CharacterEntity* parent, 		                         //親クラス
		DirectX::SimpleMath::Vector3 scale,                  //初期の大きさ
		DirectX::SimpleMath::Vector3 position,               //親の座標からどれだけ離れているか
		DirectX::SimpleMath::Quaternion rotation);           //+Zに向いているときの回転情報
	//デストラクタ
	~BirdEnemyFeather();
	//初期化
	void Initialize() override;
	//更新処理
	void Update(const float& elapsedTime) override;


private:

	State m_state;

};
