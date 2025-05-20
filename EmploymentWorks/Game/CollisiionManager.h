#pragma once
#include "Game/Entities/CollisionEntity.h"

// 前方宣言
class CommonResources;


class CollisionManager
{

public:
	//コンストラクタ
	CollisionManager();
	//デストラクタ
	~CollisionManager();
	//初期化
	void Initialize(CommonResources* resources);
	//更新
	void Update();
	//当たり判定クラスの登録
	void AddCollsion(CollisionEntity* object);
	//押し出し
	void Extrusion(CollisionEntity* object1, CollisionEntity* object2);
	//AABB同士の押し出し
	static void AABB_AABB_Extrusion(CollisionEntity* object1, CollisionEntity* object2);

private:
	// 共通リソース
	CommonResources* m_commonResources;
	//当たり判定クラスの配列
	std::vector<CollisionEntity*> m_collisionObjects;
	//押し出しの
	static std::unordered_map<int, std::function<void(CollisionEntity* object1, CollisionEntity* object2)>> m_extrusionFunction;

};