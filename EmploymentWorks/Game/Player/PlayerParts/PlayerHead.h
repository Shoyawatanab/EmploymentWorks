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
	//パーツ名
	static constexpr const char PARTSNAME[] = "Head";

public:
	//コンストラクタ
	PlayerHead(CommonResources* resources, 
		CharacterEntity* parent
		, const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);
	//デストラクタ
	~PlayerHead() override;



	//初期化
	void Initialize() override;

};

