/*
* コンポジットパターンの葉インターフェース
*/
#pragma once
#include "Game/Interface/ICharacter.h"

class ILeaf : public ICharacter
{
public:
	//デストラクタ
	virtual ~ILeaf() = default;
};
