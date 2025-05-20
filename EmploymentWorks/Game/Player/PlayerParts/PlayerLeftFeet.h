/*
* プレイヤの左足クラス
*/
#pragma once
#include "Game/Player/PlayerPartsBase.h"

namespace WataLib
{
	class Animation;
}


// 「砲塔」クラスを定義する
class PlayerLeftFeet : public PlayerPartsBase
{
private:

	//パーツ名
	static constexpr const char PARTSNAME[] = "LeftFeet";

public:
	//コンストラクタ
	PlayerLeftFeet(CommonResources* resources, 
		CharacterEntity* parent,
		DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);
	//デストラクタ
	~PlayerLeftFeet() override;


	//IObject
	//初期化
	void Initialize() override;



};

