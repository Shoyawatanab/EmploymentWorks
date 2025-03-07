/*
* プレイヤの頭クラス
*/
#pragma once
#include "Game/Player/PlayerPartsBase.h"

namespace WataLib
{
	class Animation;
}
// 「砲塔」クラスを定義する
class PlayerHead : public PlayerPartsBase
{
private:
	static constexpr const char PARTSNAME[] = "Head";

public:
	//コンストラクタ
	PlayerHead(CommonResources* resources, 
		CharacterEntity* parent,
		DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);
	//デストラクタ
	~PlayerHead() override;



	//初期化
	void Initialize() override;

};

