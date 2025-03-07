/*
* コンポジットの元となるクラスのインターフェース
*/
#pragma once
#include "Game/Interface/IComposite.h"
#include "Libraries/WataLib/Json.h"

class ICompositeRoot : public IComposite
{
public:
	//デストラクタ
	virtual ~ICompositeRoot() = default;

	virtual void Damage(int damage) = 0;

};
