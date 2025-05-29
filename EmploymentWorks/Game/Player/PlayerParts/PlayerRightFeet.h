/*
* プレイヤの右足クラス
*/
#pragma once
#include "Game/Player/PlayerPartsBase.h"

namespace WataLib
{
	class Animation;
}


// 「砲塔」クラスを定義する
class PlayerRightFeet : public PlayerPartsBase
{
private:

	//パーツ名
	static constexpr const char PARTSNAME[] = "RightFeet";

public:
	//コンストラクタ
	PlayerRightFeet(CommonResources* resources, 
		CharacterEntity* parent
		, const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);
	//デストラクタ
	~PlayerRightFeet() override;


	//IObject
	//初期化
	void Initialize() override;


};

