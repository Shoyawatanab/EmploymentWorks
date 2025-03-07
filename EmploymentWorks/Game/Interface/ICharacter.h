/*
* キャラクターのインターフェース
*/
#pragma once
#include <unordered_map>
#include "Game/Interface/IMoveObject.h"
#include "Libraries/WataLib/Json.h"

class ICharacter : public IMoveObject
{
public:

	using ANIMATIONDATAS = std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>>;

public:
	//デストラクタ
	virtual ~ICharacter() = default;
	//アニメーションの登録
	virtual void SetAnimationData(std::string animationType, ANIMATIONDATAS datas ,bool isNormalAnimation) = 0;
	//アニメーションの変更
	virtual void ChangeAnimation(std::string animationType) = 0;
	//HP関係



};



