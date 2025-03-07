/*
* 当たり判定のインターフェース
*/
#pragma once
#include "Game/Interface/IObject.h"

class CollisionManager;

namespace WataLib
{

	class Bounding;
}


class ICollisionObject : public IObject
{
public:
	enum  class CollisionType
	{
		AABB = 1 << 0
		,OBB = 1 << 1
		,SPHERE = 1 << 2
	};

	enum class CollisionTag
	{
		None = 0
		, Player = 1 << 0
		, PlayerParts  = 1 << 1
		,Stage  = 1 <<2
		,Enemy = 1 << 3
		,EnemyParts = 1 << 4
		,Boomerang = 1 << 5
		,Beam = 1 << 6
	};


public:
	//デストラクタ
	virtual ~ICollisionObject() = default;
	//タグの取得
	virtual CollisionTag GetCollisionTag() = 0;
	//当たった時に呼び出される
	virtual void OnCollisionEnter(ICollisionObject* object, CollisionTag tag) = 0;
	//当たり判定クラスに登録
	virtual void  AddCollision(CollisionManager* collsionManager) = 0;
	//当たり判定の取得
	virtual WataLib::Bounding* GetBounding() = 0;
	//当たり判定の種類の取得
	virtual const CollisionType GetCollisionType() = 0;
	//押し出しをするかどうか
	virtual const bool GetIsExtrusion() = 0;
	//当たり判定を行わないタグ
	virtual const std::vector<CollisionTag> GetNoHitDetectionTag() = 0;
	//当たったオブジェクトの取得
	virtual const std::vector<ICollisionObject*> GetHitObject() = 0;
	//当たったオブジェクトの登録
	virtual void SetHitObject(ICollisionObject* object) = 0;
	//当たったオブジェクトの削除
	virtual void DleteHitObject(ICollisionObject* object,bool& isDelete) = 0;
};
