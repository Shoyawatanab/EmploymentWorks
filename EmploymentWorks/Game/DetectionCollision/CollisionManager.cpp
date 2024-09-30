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

#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/Enemy.h"
#include "Libraries/MyLib/Bounding.h"
#include "Interface/ICollisionObject.h"
#include "Interface/IMoveCollisionObject.h"
#include "Libraries/MyLib/CollisionMesh.h"

#include "Game/Object/Enemy/Beam.h"
#include "Libraries/MyLib/Camera/TPS_Camera.h"
#include "Game/Object/Boomerang/Boomerang.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
CollisionManager::CollisionManager()
	:
	m_commonResources{},
	m_collsionObjects{},
	m_player{},
	m_enemy{}
	,m_tpsCamera{}
{

}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::Initialize(CommonResources* resources, Player* player, Enemy* enemy)
{

	m_commonResources = resources;
	m_player = player;
	m_enemy = enemy;
	m_boomerang = m_player->GetUsingBoomerang();

	//auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	//auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();





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

		CollsionObjectTag tagI = m_collsionObjects[i]->GetCollsionTag();


		for (int j = i + 1; j < m_collsionObjects.size(); j++)
		{

			CollsionObjectTag tagJ = m_collsionObjects[j]->GetCollsionTag();

			uint32_t kind = static_cast<uint32_t>(tagI) | static_cast<uint32_t>(tagJ);



			if (!CheckIsSphere(m_collsionObjects[i], m_collsionObjects[j]))
			{
				continue;
			}

			//ブーメランと岩
			if (kind == static_cast<uint32_t>(CollisionType::Boomerang_Rock))
			{

				//当たったら
				if (RockExtrusion(m_collsionObjects[i], m_collsionObjects[j]))
				{

					m_collsionObjects[i]->OnCollisionEnter(tagJ, m_hitPosition);
					m_collsionObjects[j]->OnCollisionEnter(tagI, m_hitPosition);
				
				}

				continue;

			}


			if (kind == static_cast<uint32_t>(CollisionType::Boomerang_Tree1))
			{
				if (Tree1Extrusion(m_collsionObjects[i], m_collsionObjects[j]))
				{

					m_collsionObjects[i]->OnCollisionEnter(tagJ, m_hitPosition);
					m_collsionObjects[j]->OnCollisionEnter(tagI, m_hitPosition);


				}

				continue;

			}

			if (!CheckIsBox(m_collsionObjects[i], m_collsionObjects[j]))
			{
				continue;
			}

			//どんな処理をするのか
			switch (kind)
			{
				case static_cast<uint32_t>(CollisionType::Player_Enemy):
					break;
				case static_cast<uint32_t>(CollisionType::Player_Boomerang):
					break;
				case static_cast<uint32_t>(CollisionType::Enemy_Boomerang):
					BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);
					break;
				case static_cast<uint32_t>(CollisionType::Player_Floor):
					BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);

					break;
				case static_cast<uint32_t>(CollisionType::Enemy_Floor):
					BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);

					break;
				case static_cast<uint32_t>(CollisionType::Boomerang_Floor):

					BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);

					break;
				default:
					continue;
			}

			m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
			m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);

		}
	}




	//カメラの当たり判定
	for (int i = 0; i < m_collsionObjects.size(); i++)
	{

		CollsionObjectTag tag = m_collsionObjects[i]->GetCollsionTag();


		switch (tag)
		{
			case CollsionObjectTag::None:
				break;
			case CollsionObjectTag::Player:
				break;
			case CollsionObjectTag::Enemy:
				break;
			case CollsionObjectTag::Boomerang:
				break;
			case CollsionObjectTag::Floor:
				CameraCollision(m_collsionObjects[i]);
				break;
			default:
				break;
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




/// <summary>
/// 押し出し処理
/// </summary>
/// <param name="Object1">押し出されるオブジェクト</param>
/// <param name="Object2">押されないオブジェクト</param>
void CollisionManager::BoxExtrusion(ICollisionObject* Object1, ICollisionObject* Object2)
{

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	DirectX::BoundingBox* Box1 = Object1->GetBounding()->GetBoundingBox();
	DirectX::BoundingBox* Box2 = Object2->GetBounding()->GetBoundingBox();



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
	Vector3 a = Object1->GetPos();
	a += pushBackVec;
	Object1->SetPos(a);


}

bool CollisionManager::CheckIsBox(ICollisionObject* Object1, ICollisionObject* Object2)
{
	//バウンディングボックスの取得
	DirectX::BoundingBox* Box1 = Object1->GetBounding()->GetBoundingBox();
	DirectX::BoundingBox* Box2 = Object2->GetBounding()->GetBoundingBox();

	//バウンディングボックスと当たったかどうか
	if (Box1->Intersects(*Box2))
	{
#ifdef _DEBUG

		//ボックスの色の変更
		Object1->GetBounding()->SetIsBoxHit(true);
		Object2->GetBounding()->SetIsBoxHit(true);
#endif
		return true;
	}
	return false;
}

bool CollisionManager::CheckIsSphere(ICollisionObject* Object1, ICollisionObject* Object2)
{

	//バウンディングスフィアの取得
	DirectX::BoundingSphere* Sphere1 = Object1->GetBounding()->GetBoundingSphere();
	DirectX::BoundingSphere* Sphere2 = Object2->GetBounding()->GetBoundingSphere();

	//スフィアが当たっているかどうか
	//前に＊を置いたらエラーが消えた　今後理解する
	if (Sphere1->Intersects(*Sphere2))
	{
#ifdef _DEBUG
		//スフィアの色の変更
		Object1->GetBounding()->SetIsSphereHit(true);
		Object2->GetBounding()->SetIsSphereHit(true);
#endif
		return true;
	}

	return false;
}


//岩のメッシュとの判定　内側に押し出す
bool CollisionManager::RockExtrusion(ICollisionObject* Object1, ICollisionObject* Object2)
{
	using namespace DirectX::SimpleMath;


	////Rayの方向
	////Vector3 Direction = Object2->GetPos() - Object1->GetPos();
	//Vector3 Direction = Object1->GetPos() - Object2->GetPos();

	//Direction.Normalize();
	//Vector3 Pos = Object1->GetPos();

	const std::vector<std::unique_ptr<Boomerang::RayParameter>>& rays = m_boomerang->GetRay();

	int nearIndex = 0;

	//先端座標から一番近いものを探す
	for (int i = 0; i < rays.size() - 1; i++)
	{

		float distance1 = Vector3::Distance(rays[i]->TipPosition, Object2->GetPos());
		float distance2 = Vector3::Distance(rays[i + 1]->TipPosition, Object2->GetPos());

		//1のほうが小さい
		if (distance1 < distance2)
		{
			nearIndex = i;
		}
		else
		{
			nearIndex = i + 1;
		}

	}

	//一番近いRay
	const std::unique_ptr<Boomerang::RayParameter>& nearRay = rays[nearIndex];


	//Rayの作成
	Ray ray{ nearRay->TipPosition ,nearRay->GetDirection()};

	mylib::CollisionMesh* Mesh = Object2->GetCollsionMesh();

	if (Mesh->IntersectRay(ray, &m_hitPosition,nearRay->GetLenght()))
	{

		return true;
	}

	return false;
}

bool CollisionManager::Tree1Extrusion(ICollisionObject* Object1, ICollisionObject* Object2)
{

	using namespace DirectX::SimpleMath;

	const std::vector<std::unique_ptr<Boomerang::RayParameter>>& rays = m_boomerang->GetRay();

	int nearIndex = 0;

	//先端座標から一番近いものを探す
	for (int i = 0; i < rays.size() - 1; i++)
	{

		float distance1 = Vector3::Distance(rays[i]->TipPosition, Object2->GetPos());
		float distance2 = Vector3::Distance(rays[i + 1]->TipPosition, Object2->GetPos());

		//1のほうが小さい
		if (distance1 < distance2)
		{
			nearIndex = i;
		}
		else
		{
			nearIndex = i + 1;
		}

	}

	//一番近いRay
	const std::unique_ptr<Boomerang::RayParameter>& nearRay = rays[nearIndex];


	//Rayの作成
	Ray ray{ nearRay->TipPosition ,nearRay->GetDirection() };

	mylib::CollisionMesh* Mesh = Object2->GetCollsionMesh();

	if (Mesh->IntersectRay(ray, &m_hitPosition, nearRay->GetLenght()))
	{

		return true;
	}


	return false;
}


/// <summary>
/// カメラとの当たり判定
/// </summary>
/// <param name="object"></param>
void CollisionManager::CameraCollision(ICollisionObject* object)
{


	//DirectX::BoundingBox* box = object->GetBounding()->GetBoundingBox();


	//DirectX::SimpleMath::Vector3 direction = m_tpsCamera->GetEyePosition() - m_tpsCamera->GetTargetPosition();
	//direction.Normalize();
	////カメラの座標と注視点からの線分をRayとして作成
	//DirectX::SimpleMath::Ray ray { m_tpsCamera->GetTargetPosition(), direction };
	////Ray(線分)の距離を求める
	//float distance = DirectX::SimpleMath::Vector3::Distance(m_tpsCamera->GetEyePosition(), m_tpsCamera->GetTargetPosition());

	////当たっていない
	//if (!ray.Intersects(*box, distance))
	//{
	//	return;
	//}

	//distance /= 4.5f;

	////ターゲットの座標を取得
	//DirectX::SimpleMath::Vector3 pos = m_tpsCamera->GetTargetPosition();
	////ターゲットに方向と当たった距離をかけたものを足してEyeの座標を求める
	//pos += direction * distance;


	//m_tpsCamera->SetEyePosition(pos);

}

