/*
* プレイヤクラス　
*/

#pragma once

#include "CollisionEntity.h"


class MoveEntity : public CollisionEntity
{
public:
	//コンストラク
	MoveEntity(CommonResources* resources
		, const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);
	//デストラクタ
	~MoveEntity() override;

	//初期化
	void Initialize() override;
	//更新処理
	void  Update(const float& elapsedTime) override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//当たった時に呼び出される
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;

};


