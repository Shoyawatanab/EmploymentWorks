/*
* プレイヤの体クラス
*/

#pragma once
#include "Game/Player/PlayerPartsBase.h"


//前方宣言
namespace WataLib
{
	class Animation;
}

// 「砲塔」クラスを定義する
class PlayerBody : public PlayerPartsBase
{

private:
	//パーツ名
	static constexpr const char PARTSNAME[] = "Body";


public:
	//コンストラクタ
	PlayerBody(CommonResources* resources 
		, CharacterEntity* parent 		                         //親クラス
		, const DirectX::SimpleMath::Vector3& scale                  //初期の大きさ
		, const DirectX::SimpleMath::Vector3& position               //親の座標からどれだけ離れているか
		, const DirectX::SimpleMath::Quaternion& rotation);           //+Zに向いているときの回転情報
	//デストラクタ
	~PlayerBody() override;

	//IObject
	//初期化
	void Initialize() override;



};

