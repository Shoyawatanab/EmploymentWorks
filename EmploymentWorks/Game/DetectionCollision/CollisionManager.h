#pragma once
/*
	@file	CollisionManager.h.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "pch.h"
#include "Game/Object/Boomerang/Boomerang.h"

// 前方宣言
class CommonResources;
class ICollsionObject;


class CollisionManager final 

{
public:


private:
	// 共通リソース
	CommonResources* m_commonResources;
	Player* m_player;
	Enemy* m_enemy;

	//当たり判定オブジェクトの登録配列 
	std::vector<ICollisionObject*> m_collsionObjects;

public:
	CollisionManager();

	void Update();

	void AddCollsion(ICollisionObject* object);
private:
};
