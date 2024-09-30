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


namespace mylib
{
	class TPS_Camera;

}



class CollisionManager final

{
public:

	void SetTPS_Camera(mylib::TPS_Camera* camera) { m_tpsCamera = camera; }


private:
	// 共通リソース
	CommonResources* m_commonResources;
	Player* m_player;
	Enemy* m_enemy;
	Boomerang* m_boomerang;

	//当たり判定オブジェクトの登録配列 
	std::vector<ICollisionObject*> m_collsionObjects;

	// ポリゴンとRayが衝突した座標
	DirectX::SimpleMath::Vector3 m_hitPosition;



	//ビームのバウンディング
	std::vector<Bounding> m_beamBounding;

	//ゲームカメラ プレイ中のカメラ
	mylib::TPS_Camera* m_tpsCamera;

public:
	CollisionManager();
	~CollisionManager();


	void Initialize(CommonResources* resources, Player* player, Enemy* enemy);


	void Update();

	void AddCollsion(ICollisionObject* object);

	void BoxExtrusion(ICollisionObject* Object1, ICollisionObject* Object2);

	bool CheckIsBox(ICollisionObject* Object1, ICollisionObject* Object2);

	bool CheckIsSphere(ICollisionObject* Object1, ICollisionObject* Object2);

	bool RockExtrusion(ICollisionObject* Object1, ICollisionObject* Object2);

	bool Tree1Extrusion(ICollisionObject* Object1, ICollisionObject* Object2);

	void CameraCollision(ICollisionObject* object);


private:
};
