#pragma once
/*
	@file	Wall.h.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Entities/INotMoveEntity.h"

namespace WataLib
{
	class Bounding;
}


class Wall : public INotMoveEntity

{
public:
	//コンストラクタ
	Wall(CommonResources* resources
		,DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);

	//デストラクタ
	~Wall() override;

	//IObject
		//初期化
	void Initialize() override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//更新処理
	void  Update(const float& elapsedTime) override;

	//ICollisionObject
	//タグの取得
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::Stage; };
	//当たった時に呼び出される
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//当たり判定の種類の取得
	const CollisionType GetCollisionType() override { return CollisionType::AABB; };
	//押し出しをするかどうか
	const bool GetIsExtrusion() override { return false; };
	//当たり判定を行わないタグ
	const std::vector<CollisionTag> GetNoHitDetectionTag() {
		return  {
			{CollisionTag::Stage }
		};
	};



	//INotMoveObject
	//基本情報の設定
	void SetDatas(DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);

private:
	// モデル
	std::unique_ptr<DirectX::Model> m_model;




};
