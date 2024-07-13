/*
	@file	CollisionManager.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "CollisionManager.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Object/Player.h"
#include "Game/Object/Enemy/Enemy.h"
#include "Libraries/MyLib/Bounding.h"
#include "Interface/ICollisionObject.h"
#include "Interface/IMoveCollisionObject.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
CollisionManager::CollisionManager()
	:
	m_commonResources{},
	m_collsionObjects{},
	m_player{},
	m_enemy{}
{
}



//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void CollisionManager::Update()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//バウンディングの色のリセット
	for (auto& object : m_collsionObjects)
	{
		object->GetBounding()->SetIsBoxHit(false);
		object->GetBounding()->SetIsSphereHit(false);

	}


	//登録されたオブジェクト全てと当たり判定を取る
	for (int i = 0; i < m_collsionObjects.size() - 1; i++)
	{
		for (int j = i + 1; j < m_collsionObjects.size(); j++)
		{
			CollsionObjectTag tagI = m_collsionObjects[i]->GetCollsionTag();
			CollsionObjectTag tagJ = m_collsionObjects[j]->GetCollsionTag();

			if (tagI == CollsionObjectTag::Player && tagJ == CollsionObjectTag::Boomerang ||
				tagJ == CollsionObjectTag::Player && tagI == CollsionObjectTag::Boomerang)
			{
				continue;
			}

			//バウンディングクラスの取得
			Bounding* bounding1 = m_collsionObjects[i]->GetBounding();
			Bounding* bounding2 = m_collsionObjects[j]->GetBounding();

			//バウンディングスフィアの取得
			DirectX::BoundingSphere* Sphere1 = bounding1->GetBoundingSphere();
			DirectX::BoundingSphere* Sphere2 = bounding2->GetBoundingSphere();

			
			//スフィアが当たっているかどうか
			//前に＊を置いたらエラーが消えた　今後理解する
			if (!Sphere1->Intersects(*Sphere2))
			{
				continue;
			}
			if (tagI != CollsionObjectTag::NotMoveObject || tagJ != CollsionObjectTag::NotMoveObject)
			{

			}

			//スフィアの色の変更
			bounding1->SetIsSphereHit(true);
			bounding2->SetIsSphereHit(true);



			//バウンディングボックスの取得
			DirectX::BoundingBox* Box1 = bounding1->GetBoundingBox();
			DirectX::BoundingBox* Box2 = bounding2->GetBoundingBox();

			//バウンディングボックスと当たったかどうか
			if (!Box1->Intersects(*Box2))
			{
				continue;
			}

			//ボックスの色の変更
			bounding1->SetIsBoxHit(true);
			bounding2->SetIsBoxHit(true);


			if (tagI == CollsionObjectTag::Boomerang && tagJ == CollsionObjectTag::Enemy ||
				tagJ == CollsionObjectTag::Boomerang && tagI == CollsionObjectTag::Enemy)
			{

				m_collsionObjects[i]->OnCollision(tagJ);
				m_collsionObjects[j]->OnCollision(tagI);



				return;
			}


			//ボックス同士の当たり判定


			Vector3 Min1 = Box1->Center - Box1->Extents;
			Vector3 Max1 = Box1->Center + Box1->Extents;
			Vector3 Min2 = Box2->Center - Box2->Extents;
			Vector3 Max2 = Box2->Center + Box2->Extents;

			
			//各軸の差分の計算
			float dx1 = Max2.x - Min1.x;
			float dx2 = Min2.x - Max1.x;
			float dy1 = Max2.y - Min1.y;
			float dy2 = Min2.y - Max1.y;
			float dz1 = Max2.z - Min1.z;
			float dz2 = Min2.z - Max1.z;

			//各軸の絶対値の小さい方を軸のめり込みにする
			float dx = abs(dx1) < abs(dx2) ? dx1 : dx2;
			float dy = abs(dy1) < abs(dy2) ? dy1 : dy2;
			float dz = abs(dz1) < abs(dz2) ? dz1 : dz2;

			// 押し戻しベクトル
			Vector3 pushBackVec = Vector3::Zero;

			// めり込みが一番小さい軸を押し戻す
			if (abs(dx) <= abs(dy) && abs(dx) <= abs(dz))
			{
				pushBackVec.x += dx;
			}
			else if (abs(dz) <= abs(dx) && abs(dz) <= abs(dy))
			{
				pushBackVec.z += dz;
			}
			else
			{
				pushBackVec.y += dy;
			}

			//押し出す
			//押す側と押される側をどうするか　
			//座標の更新の仕方
			Vector3 a = m_collsionObjects[i]->GetPos();
			a += pushBackVec;
			m_collsionObjects[i]->SetPos(a);
	
		}
	}


}

/// <summary>
///配列にオブジェクトの登録 
/// </summary>
/// <param name="object"></param>
void CollisionManager::AddCollsion(ICollisionObject* object)
{
	m_collsionObjects.emplace_back(object);
}

