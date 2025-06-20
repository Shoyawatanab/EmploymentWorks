#pragma once
#include "GameBase/Component.h"
#include "GameBase/Component/Transform/Transform.h"

class CommonResources;

//判定時のタイプ
enum class CollisionType
{

	FIXED     = 1 ,	   //固定
	COLLISION = 2,	   //移動
	TRIGGER   = 3      //すり抜け

};


class ColliderComponent : public Component
{
public:

	//当たり判定の種類
	enum  class ColliderTag
	{
		AABB = 1 << 0
		, OBB = 1 << 1
		, SPHERE = 1 << 2
	};

public:	
	//当たり判定の種類の取得
	const ColliderTag GetCollisionTag() { return m_collisionTag; }
	//判定時の種類の取得
	CollisionType GetCollisionType() const { return m_collisionType; }

	//当たったコライダーの取得
	const std::vector<ColliderComponent*> GetHitObject() { return m_hitCollider; };
	//当たったコライダーの登録
	void SetHitObject(ColliderComponent* ColliderComponent) { m_hitCollider.push_back(ColliderComponent); };
	//押し出し
	void SetPushBack(DirectX::SimpleMath::Vector3 puchBackVector);

public:
	//コンストラクタ
	ColliderComponent(Actor* owner,ColliderTag tag , CollisionType type);

	//デストラクタ
	virtual ~ColliderComponent() override;

	// 更新処理
	void Update(const float& deltaTime) override;
	//派生用の更新処理
	virtual void UpdateCollider() {};
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection
	, DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch
	, DirectX::BasicEffect* effect
	, ID3D11InputLayout* inputlayout);
	//派生用の描画処理
	virtual void RenderCollider(const DirectX::SimpleMath::Matrix& view,const DirectX::SimpleMath::Matrix& projection
		, DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch
		, DirectX::BasicEffect* effect
		, ID3D11InputLayout* inputlayout) {
		UNREFERENCED_PARAMETER(view);
		UNREFERENCED_PARAMETER(projection);
		UNREFERENCED_PARAMETER(batch);
		UNREFERENCED_PARAMETER(effect);
		UNREFERENCED_PARAMETER(inputlayout);
	};


	//当たったコライダーの削除
	bool DleteHitObject(ColliderComponent* object);

	//座標の更新
	virtual void PositionUpdate() = 0;

private:

	//当たり判定の種類
	ColliderTag m_collisionTag;
	//判定時の種類
	CollisionType m_collisionType;
	//当たったオブジェクトの格納変数
	std::vector<ColliderComponent*> m_hitCollider;


};


class AABB : public ColliderComponent
{
public:
	//バウンディングボックスの取得
	DirectX::BoundingBox* GetBoundingBox();
	//バウンディングスフィアの取得
	DirectX::BoundingSphere* GetBoundingSphere();
	//DirectX::BoundingOrientedBox* GetOrientedBox() { return m_orientexBox.get(); }

public:
	//コンストラクタ
	AABB(Actor* owner, ColliderTag tag, CollisionType type
	,const DirectX::SimpleMath::Vector3& extents
	, const float& radius);
	//デストラクタ
	~AABB() override;

	//派生用の更新処理
	void UpdateCollider() override ;
	//派生用の描画処理
	void RenderCollider(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection
		, DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch
		, DirectX::BasicEffect* effect
		, ID3D11InputLayout* inputlayout) override;

	//座標の更新
	void PositionUpdate() override;


private:
	//バウンディングボックス
	std::unique_ptr<DirectX::BoundingBox> m_boundingBox;
	//バウンディングスフィア
	std::unique_ptr<DirectX::BoundingSphere> m_boundingSphere;


};