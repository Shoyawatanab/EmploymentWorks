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
#include "Game/Object/Enemy/BossEnemy.h"
#include "Libraries/MyLib/Bounding.h"
#include "Interface/ICollisionObject.h"
#include "Interface/IMoveCollisionObject.h"
#include "Libraries/MyLib/CollisionMesh.h"

#include "Game/Object/Enemy/Beam.h"
#include "Libraries/MyLib/Camera/TPS_Camera.h"

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

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();



	// コリジョンメッシュを生成する
	m_collisionMesh = std::make_unique<mylib::CollisionMesh>();
	//大きさをー0.1して壁にめり込まないようにしている
	m_collisionMesh->Initialize(device, context, L"Stage", DirectX::SimpleMath::Vector3::Zero, 7.9f);



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



			//スフィアの当たり判定
			if (!CheckIsSphere(m_collsionObjects[i], m_collsionObjects[j]))
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
				case static_cast<uint32_t>(CollisionType::Player_Stage):

					//ボックスとの当たり判定
					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{
						//押し出し処理
						BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);
						//それぞれのクラスの判定
						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);

					}
					break;
				case static_cast<uint32_t>(CollisionType::Player_Floor):
					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{
						BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);
						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);
					}
					break;
				case static_cast<uint32_t>(CollisionType::Player_Pillar):
					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{
						BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);
						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);
					}


					break;
				case static_cast<uint32_t>(CollisionType::Player_Artillery):
					break;
				case static_cast<uint32_t>(CollisionType::Player_ArtilleryBullet):
					break;


				case static_cast<uint32_t>(CollisionType::Enemy_Boomerang):
					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{

						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);

					}

					break;
				case static_cast<uint32_t>(CollisionType::Enemy_Stage):

					//if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					//{
					//	BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);
					//	m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
					//	m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);
					//}

					//敵のほうが先に登録されているから引数がJ　I　の順番
					if (CheckIsOrientexdBoxToBox(m_collsionObjects[j], m_collsionObjects[i]))
					{
						BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);
						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);

					}

					break;
				case static_cast<uint32_t>(CollisionType::Enemy_Floor):
					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{
						//押し出し処理
						BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);

						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);


					}
					break;
				case static_cast<uint32_t>(CollisionType::Enemy_Pillar):
					break;
				case static_cast<uint32_t>(CollisionType::Enemy_Artillery):
					break;
				case static_cast<uint32_t>(CollisionType::Enemy_ArtilleryBullet):
					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{

						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);

					}

					break;


				case static_cast<uint32_t>(CollisionType::Boomerang_Stage):
					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{
						BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);
						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);


					}
					break;
				case static_cast<uint32_t>(CollisionType::Boomerang_Floor):
					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{
						BoxExtrusion(m_collsionObjects[i], m_collsionObjects[j]);
						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);


					}
					break;
				case static_cast<uint32_t>(CollisionType::Boomerang_Pillar):
					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{

						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);

					}

					break;
				case static_cast<uint32_t>(CollisionType::Boomerang_Artillery):

					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{

						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);

					}
					break;

					break;
				case static_cast<uint32_t>(CollisionType::Boomerang_ArtilleryBullet):
					break;

				case static_cast<uint32_t>(CollisionType::ArtilleryBullet_Stage):
					
					if (CheckIsBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{
						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);

					}

					break;


				

				case static_cast<uint32_t>(CollisionType::EnemyParts_Boomerang):
					if (CheckIsOrientexdBoxToBox(m_collsionObjects[i], m_collsionObjects[j]))
					{

						m_collsionObjects[i]->OnCollisionEnter(tagJ, m_collsionObjects[j]->GetBounding()->GetBoundingBox()->Center);
						m_collsionObjects[j]->OnCollisionEnter(tagI, m_collsionObjects[i]->GetBounding()->GetBoundingBox()->Center);
					}
					break;
				default:
					continue;
			}

		}
	}

	BeamAndPlayerCollision();


	DirectX::SimpleMath::Vector3 targetPosition = m_tpsCamera->GetTargetPosition();
	DirectX::SimpleMath::Vector3 eyePosition = m_tpsCamera->GetEyePosition();

	float distance = Vector3::Distance(targetPosition, eyePosition);

	//カメラの当たり判定
	for (int i = 0; i < m_collsionObjects.size(); i++)
	{

		CollsionObjectTag tag = m_collsionObjects[i]->GetCollsionTag();


		//ものによってRayの長さが変わるからtagで判定する
		switch (tag)
		{
			case CollsionObjectTag::Stage:
				CameraCollision(m_collsionObjects[i], distance);
				break;
			case CollsionObjectTag::Floor:
				CameraCollision(m_collsionObjects[i],distance);
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
	Vector3 a = Object1->GetPosition();
	a += pushBackVec;
	Object1->SetPosition(a);


}

/// <summary>
/// AABBの当たり判定
/// </summary>
/// <param name="Object1"></param>
/// <param name="Object2"></param>
/// <returns></returns>
bool CollisionManager::CheckIsBoxToBox(ICollisionObject* Object1, ICollisionObject* Object2)
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

/// <summary>
/// OBB  BoundingBox To BoundingOrientexsBox
/// </summary>
/// <param name="Object1">BoundingBox</param>
/// <param name="Object2">BoundingOrientedBox</param>
/// <returns></returns>
bool CollisionManager::CheckIsOrientexdBoxToBox(ICollisionObject* Object1, ICollisionObject* Object2)
{
	//バウンディングボックスの取得
	DirectX::BoundingBox* Box1 = Object1->GetBounding()->GetBoundingBox();
	DirectX::BoundingOrientedBox* Box2 = Object2->GetBounding()->GetOrientedBox();

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

/// <summary>
/// OBB  BoundingOrientexsBox To BoundingOrientexsBox
/// </summary>
/// <param name="Object1">BoundingOrientexsBox</param>
/// <param name="Object2">BoundingOrientexsBox</param>
/// <returns></returns>
bool CollisionManager::CheckIsOrientexdBoxToOrientexdBox(ICollisionObject* Object1, ICollisionObject* Object2)
{
	//バウンディングボックスの取得
	DirectX::BoundingOrientedBox* Box1 = Object1->GetBounding()->GetOrientedBox();
	DirectX::BoundingOrientedBox* Box2 = Object2->GetBounding()->GetOrientedBox();

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


//壁との判定　内側に押し出す
bool CollisionManager::WallExtrusion(ICollisionObject* Object1, ICollisionObject* Object2)
{
	using namespace DirectX::SimpleMath;

	//Rayの方向
	Vector3 Direction = Object2->GetPosition() - Object1->GetPosition();
	Direction.Normalize();

	//Rayの作成
	Ray ray{ Object1->GetPosition(),Direction };


	if (m_collisionMesh->IntersectRay(ray, &m_hitPosition))
	{

		Object1->SetPosition(m_hitPosition);

		return true;
	}

	return false;
}

void CollisionManager::BeamAndPlayerCollision()
{

	//プレイヤとビーム
	if (m_player->GetPlayerState() != m_player->GetPlayerUsually() && !m_enemy->GetIsAttack())
	{
		return;
	}



	//ビームのBoundinの取得
	std::vector<std::unique_ptr<Bounding>>& BeamBounding = m_enemy->GetBeam()->GetBounding();

	//プレイヤのBoundingSphereの取得
	DirectX::BoundingSphere* PlayerBoundingSphere = m_player->GetBounding()->GetBoundingSphere();

	for (auto& beam : BeamBounding)
	{

		DirectX::BoundingSphere* Sphere = beam->GetBoundingSphere();

		//当たったら
		if (PlayerBoundingSphere->Intersects(*Sphere))
		{
			if (m_player->GetPlayerState() == m_player->GetPlayerUsually() && !m_player->GetIsInvincible())
			{
				float hp = m_player->GetPlayerHP();
				hp--;
				m_player->SetPlayerHP(hp);
				//プレイヤを無敵状態に
				m_player->SetIsInvincible(true);

			}

			//飛ぶ方向を求める
			m_player->DemandBlownAwayDirection(Sphere->Center);

			//プレイヤの状態を飛ばされるに変更
			m_player->ChangeState(m_player->GetPlayerBlownAway());

			return;
		}

	}


}

/// <summary>
/// カメラとの当たり判定
/// </summary>
/// <param name="object"></param>
void CollisionManager::CameraCollision(ICollisionObject* object, float rayDistance)
{


	DirectX::BoundingBox* box = object->GetBounding()->GetBoundingBox();


	DirectX::SimpleMath::Vector3 direction = m_tpsCamera->GetEyePosition() - m_tpsCamera->GetTargetPosition();
	direction.Normalize();
	//カメラの座標と注視点からの線分をRayとして作成
	DirectX::SimpleMath::Ray ray { m_tpsCamera->GetTargetPosition(), direction };
	//Ray(線分)の距離を求める
	float distance = DirectX::SimpleMath::Vector3::Distance(m_tpsCamera->GetEyePosition(), m_tpsCamera->GetTargetPosition());
	distance = 1;
	//当たっていない
	if (!ray.Intersects(*box, distance))
	{
		return;
	}

	//距離によって当たったかどうか判定
	if (distance > rayDistance)
	{
		return;
	}

	//distance /= 4.5f;

	//ターゲットの座標を取得
	DirectX::SimpleMath::Vector3 pos = m_tpsCamera->GetTargetPosition();
	//ターゲットに方向と当たった距離をかけたものを足してEyeの座標を求める
	pos += direction * distance;


	m_tpsCamera->SetEyePosition(pos);

}

