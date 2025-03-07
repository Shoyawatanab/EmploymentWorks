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
	//static constexpr コンパイル時に決定する　クラス外での変更をする必要がないため
	//static cons      クラス外で変更する可能性がある場合

	static constexpr const char PARTSNAME[] = "Body";


public:
	//コンストラクタ
	PlayerBody(CommonResources* resources, 
		CharacterEntity* parent, 		                         //親クラス
		DirectX::SimpleMath::Vector3 scale,                  //初期の大きさ
		DirectX::SimpleMath::Vector3 position,               //親の座標からどれだけ離れているか
		DirectX::SimpleMath::Quaternion rotation);           //+Zに向いているときの回転情報
	//デストラクタ
	~PlayerBody() override;

	//IObject
	//初期化
	void Initialize() override;



};

