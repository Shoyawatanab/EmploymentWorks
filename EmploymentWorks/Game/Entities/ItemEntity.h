/*
* プレイヤクラス　
*/

#pragma once

#include "MoveEntity.h"
#include <unordered_map>
#include "Libraries/WataLib/Json.h"

namespace WataLib
{
	class Animation;
}

class ItemEntity : public MoveEntity
{
public:


	ItemEntity(CommonResources* resources
		,const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);

	~ItemEntity() override;

//BaseEntity
	//初期化
	void Initialize();
	//更新処理
	void  Update(const float& elapsedTime)  override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
//CollisionEntity
	//当たった時に呼び出される
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;

	//回収時
	virtual void OnAcquired() {}

private:



};


