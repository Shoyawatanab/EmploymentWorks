/*
* 動くオブジェクトのインターフェース
*/
#pragma once
//#include "pch.h"
#include "Game/Interface/ICollisionObject.h"

class IMoveObject : public ICollisionObject
{
public:
	//デストラクタ
	virtual ~IMoveObject() = default;
	//更新処理
	virtual void  Update(const float& elapsedTime) = 0;


};
