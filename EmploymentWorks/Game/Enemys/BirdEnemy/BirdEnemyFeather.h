/*
	@file	BirdEnemyFeather.h
	@brief　鳥の敵の羽
*/
#pragma once
#include "Game/Enemys/BirdEnemy/BirdEnemyPartsBase.h"


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BirdEnemyFeather : public BirdEnemyPartsBase
{
public:
	static constexpr const char PARTSNAME[] = "Body";

public:
	enum class State
	{
		Up
		,Down
	};

	State m_state;

public:
	BirdEnemyFeather(CommonResources* resources, 
		CharacterEntity* parent, 		                         //親クラス
		DirectX::SimpleMath::Vector3 scale,                  //初期の大きさ
		DirectX::SimpleMath::Vector3 position,               //親の座標からどれだけ離れているか
		DirectX::SimpleMath::Quaternion rotation);           //+Zに向いているときの回転情報
	
	~BirdEnemyFeather();
	//初期化
	void Initialize() override;

	void Update(const float& elapsedTime) override;

};
