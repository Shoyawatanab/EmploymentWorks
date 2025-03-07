/*
* 動かないオブジェクトのインターフェース
*/
#pragma once
#include "Game/Interface/ICollisionObject.h"


class INotMoveObject : public ICollisionObject
{
public:
	//デストラクタ
	virtual ~INotMoveObject() = default;

	//基本情報の設定
	virtual void SetDatas(DirectX::SimpleMath::Vector3 scale, 
		DirectX::SimpleMath::Vector3 position, 
		DirectX::SimpleMath::Quaternion rotation) = 0;

};
