/*
* プレイヤの左腕クラス
*/
#pragma once
#include "Game/Player/PlayerPartsBase.h"

namespace WataLib
{
	class Animation;
}


// 「砲塔」クラスを定義する
class PlayerLeftArm : public PlayerPartsBase
{
private:
	//パーツ名
	static constexpr const char PARTSNAME[] = "LeftArm";

public:
	//コンストラクタ
	PlayerLeftArm(CommonResources* resources, 
		CharacterEntity* parent,
		DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);
	//デストラクタ
	~PlayerLeftArm() override;


	//初期化
	void Initialize() override;


};

