/*
* プレイヤの右ア腕クラス
*/
#pragma once
#include "Game/Player/PlayerPartsBase.h"

namespace WataLib
{
	class Animation;
}

// 「砲塔」クラスを定義する
class PlayerRightArm : public PlayerPartsBase
{
private :

	//パーツ名
	static constexpr const char PARTSNAME[] = "RightArm";

public:
	//コンストラクタ
	PlayerRightArm(CommonResources* resources, 
		CharacterEntity* parent,
		DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);
	//デストラクタ
	~PlayerRightArm() override;


	//IObject
	//初期化
	void Initialize() override;


};

