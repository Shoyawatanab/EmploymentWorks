#include "pch.h"
#include "DetectionCollision.h"
#include "Libraries/WataLib/Bounding.h"

using namespace DirectX::SimpleMath;


std::unordered_map<int, std::function<void(CollisionEntity* object1, CollisionEntity* object2, bool& isHit)>> WataLib::DetectionCollision::m_detectionFunction = {
	{(int)CollisionEntity::CollisionType::AABB    | (int)CollisionEntity::CollisionType::AABB,    DetectionCollision::AABB_AABB}
	,{(int)CollisionEntity::CollisionType::OBB    | (int)CollisionEntity::CollisionType::OBB,     DetectionCollision::OBB_OBB}
	,{(int)CollisionEntity::CollisionType::SPHERE | (int)CollisionEntity::CollisionType::SPHERE,  DetectionCollision::SPHERE_SPHERE}
	,{(int)CollisionEntity::CollisionType::AABB   | (int)CollisionEntity::CollisionType::OBB,     DetectionCollision::AABB_OBB}
	,{(int)CollisionEntity::CollisionType::AABB   | (int)CollisionEntity::CollisionType::SPHERE,  DetectionCollision::AABB_SPHERE}

};


void WataLib::DetectionCollision::CheckHit(CollisionEntity* object1, CollisionEntity* object2, bool& isHit)
{

	//元のデータに影響を与えないため　入れ替えをするため
	CollisionEntity* localObject1 = object1;
	CollisionEntity* localObject2 = object2;

	//並び替え　小さいほうをObject1にするようにする
	(int)localObject1->GetCollisionType() > (int)localObject2->GetCollisionType() ? std::swap(localObject1, localObject2) : void();

	int type = (int)localObject1->GetCollisionType() | (int)localObject2->GetCollisionType();

	//当たり判定の種類があるか
	auto it = m_detectionFunction.find(type);

	
	if (it != m_detectionFunction.end())
	{
		//あれば登録された関数を呼ぶ
		m_detectionFunction[type](localObject1, localObject2, isHit);

	}

}

void WataLib::DetectionCollision::AABB_AABB(CollisionEntity* object1, CollisionEntity* object2, bool& isHit)
{
	//スフィア同士の判定
	SPHERE_SPHERE(object1, object2,isHit);

	//当たっていない
	if (!isHit)
	{
		//フラグを当たっていないに
		isHit = false;
		return;
	}

	//フラグを当たっていないに
	isHit = false;

	//データの取得
	DirectX::BoundingBox* Box1 = object1->GetBounding()->GetBoundingBox();
	DirectX::BoundingBox* Box2 = object2->GetBounding()->GetBoundingBox();

	//判定
	if (Box1->Intersects(*Box2))
	{
		//当たった
		isHit = true;
		return;
	}

	//当たってない
	isHit = false;
}

void WataLib::DetectionCollision::OBB_OBB(CollisionEntity* object1, CollisionEntity* object2, bool& isHit)
{

	//スフィア同士の判定
	SPHERE_SPHERE(object1, object2, isHit);

	//当たっていない
	if (!isHit)
	{
		//フラグを当たっていないに
		isHit = false;
		return;
	}
	//フラグを当たっていないに
	isHit = false;

	//データの取得
	DirectX::BoundingOrientedBox* Box1 = object1->GetBounding()->GetOrientedBox();
	DirectX::BoundingOrientedBox* Box2 = object2->GetBounding()->GetOrientedBox();

	//判定
	if (Box1->Intersects(*Box2))
	{
		//当たった
		isHit = true;
		return;
	}

	//当たってない
	isHit = false;

}

void WataLib::DetectionCollision::SPHERE_SPHERE(CollisionEntity* object1, CollisionEntity* object2, bool& isHit)
{
	DirectX::BoundingSphere* Sphere1 = object1->GetBounding()->GetBoundingSphere();
	DirectX::BoundingSphere* Sphere2 = object2->GetBounding()->GetBoundingSphere();

	//判定
	if (Sphere1->Intersects(*Sphere2))
	{
		//当たった
		isHit = true;
		return;
	}

	//当たってない
	isHit = false;

}

void WataLib::DetectionCollision::AABB_OBB(CollisionEntity* object1, CollisionEntity* object2, bool& isHit)
{
	//スフィア同士の判定
	SPHERE_SPHERE(object1, object2, isHit);

	//当たっていない
	if (!isHit)
	{
		//フラグを当たっていないに
		isHit = false;
		return;
	}
	//フラグを当たっていないに
	isHit = false;

	//データの取得
	DirectX::BoundingBox* Box1 = object1->GetBounding()->GetBoundingBox();
	DirectX::BoundingOrientedBox* Box2 = object2->GetBounding()->GetOrientedBox();

	//判定
	if (Box1->Intersects(*Box2))
	{		
		//当たった
		isHit = true;
		return;
	}

	//当たってない
	isHit = false;

}

void WataLib::DetectionCollision::AABB_SPHERE(CollisionEntity* object1, CollisionEntity* object2, bool& isHit)
{
	//スフィア同士の判定
	SPHERE_SPHERE(object1, object2, isHit);

	//当たっていない
	if (!isHit)
	{
		//フラグを当たっていないに
		isHit = false;
		return;
	}
	//フラグを当たっていないに
	isHit = false;

	//データの取得
	DirectX::BoundingBox* Box = object1->GetBounding()->GetBoundingBox();
	DirectX::BoundingSphere* Sphere = object2->GetBounding()->GetBoundingSphere();

	//判定
	if (Box->Intersects(*Sphere))
	{
		//当たった
		isHit = true;
		return;
	}

	//当たってない
	isHit = false;

}

bool WataLib::DetectionCollision::Circle_RectCheckHit(const DirectX::SimpleMath::Vector2& circleCenter, float circleRadius,
	const DirectX::SimpleMath::Vector2& rectCenter, float rectWidth, float rectHeight)
{
	

	// 四角形の境界座標を計算
	float rectLeft = rectCenter.x - rectWidth / 2;
	float rectRight = rectCenter.x + rectWidth / 2;
	float rectTop = rectCenter.y - rectHeight / 2;
	float rectBottom = rectCenter.y + rectHeight / 2;

	// 円の中心に最も近い四角形の点を求める
	float closestX = std::max(rectLeft, std::min(circleCenter.x, rectRight));
	float closestY = std::max(rectTop, std::min(circleCenter.y, rectBottom));

	// 円の中心と最近接点の距離を計算
	Vector2 diff = circleCenter - Vector2(closestX, closestY);
	float distanceSquared = diff.LengthSquared();

	// 当たり判定（距離の二乗が半径の二乗以下なら衝突）
	return distanceSquared <= (circleRadius * circleRadius);

}
