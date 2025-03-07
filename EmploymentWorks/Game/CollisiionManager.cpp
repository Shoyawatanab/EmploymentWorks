#include "pch.h"
#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/DetectionCollision.h"

#include "Libraries/WataLib/Bounding.h"

using namespace DirectX::SimpleMath;


std::unordered_map<int, std::function<void(CollisionEntity* object1, CollisionEntity* object2)>> CollisionManager::m_extrusionFunction = {
	{(int)CollisionEntity::CollisionType::AABB | (int)CollisionEntity::CollisionType::AABB,CollisionManager::AABB_AABB_Extrusion}

};




/// <summary>
/// コンストラクタ
/// </summary>
CollisionManager::CollisionManager()
{
}

/// <summary>
/// デストラクタ
/// </summary>
CollisionManager::~CollisionManager()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void CollisionManager::Initialize(CommonResources* resources)
{

	m_commonResources = resources;

}

/// <summary>
/// 更新
/// </summary>
void CollisionManager::Update()
{

	for (int i = 0; i < m_collisionObjects.size() - 1; i++)
	{
		//アクティブ状態で牌場合
		if (!m_collisionObjects[i]->GetIsEntityActive())
		{
			continue;
		}

		//当たり判定を行わないTagの取得
		std::vector<CollisionEntity::CollisionTag> tags = m_collisionObjects[i]->GetNoHitDetectionTag();

		for (int j = i + 1; j < m_collisionObjects.size(); j++)
		{

			//アクティブ状態で牌場合
			if (!m_collisionObjects[j]->GetIsEntityActive())
			{
				continue;
			}


			//Tagの取得
			CollisionEntity::CollisionTag tag = m_collisionObjects[j]->GetCollisionTag();

			//当たり判定を行わないかどうかの判定
			if (std::find(tags.begin(), tags.end(),tag) != tags.end())
			{
				//行わない
				continue;
			}

			bool isHit = false;

			//あたったかどうか
			WataLib::DetectionCollision::CheckHit(m_collisionObjects[i], m_collisionObjects[j], isHit);
			
			//当たったら
			if (isHit)
			{
				//押し出し
				Extrusion(m_collisionObjects[i], m_collisionObjects[j]);

				//当たったオブジェクトの取得
				std::vector<CollisionEntity*> ob = m_collisionObjects[i]->GetHitObject();

				//すでに当たっているかどうか
				if (std::find(ob.begin(), ob.end(), m_collisionObjects[j]) != ob.end())
				{
					//当たり続けているときの呼ぶ関数

				}
				else
				{
					//当たった時だけ呼ぶ関数
					m_collisionObjects[i]->OnCollisionEnter(m_collisionObjects[j], m_collisionObjects[j]->GetCollisionTag());
					m_collisionObjects[j]->OnCollisionEnter(m_collisionObjects[i], m_collisionObjects[i]->GetCollisionTag());
					//当たったオブジェクトのポインタを登録
					m_collisionObjects[i]->SetHitObject(m_collisionObjects[j]);

				}


			}
			//当たっていないなら
			else
			{
				bool isDelete = false;
				m_collisionObjects[i]->DleteHitObject(m_collisionObjects[j],isDelete);
				//削除できたら
				if (isDelete)
				{
					//離れた時に呼ぶ関数

				}

			}



		}

	}

}

/// <summary>
/// 当たり判定の追加
/// </summary>
/// <param name="object">追加するクラス</param>
void CollisionManager::AddCollsion(CollisionEntity* object)
{

	m_collisionObjects.push_back(object);

}

/// <summary>
/// 押し出し
/// </summary>
/// <param name="object1">オブジェクト１</param>
/// <param name="object2">オブジェクト２</param>
void CollisionManager::Extrusion(CollisionEntity* object1, CollisionEntity* object2)
{

	int type = (int)object1->GetCollisionType() | (int)object2->GetCollisionType();

	//当たり判定の種類があるか
	auto it = m_extrusionFunction.find(type);


	if (it != m_extrusionFunction.end())
	{
		//あれば登録された関数を呼ぶ
		m_extrusionFunction[type](object1,object2);

	}





}

/// <summary>
/// AABBの押し出し
/// </summary>
/// <param name="object1">オブジェクト１</param>
/// <param name="object2">オブジェクト２</param>
void CollisionManager::AABB_AABB_Extrusion(CollisionEntity* object1, CollisionEntity* object2)
{

	DirectX::BoundingBox* Box1 = object1->GetBounding()->GetBoundingBox();
	DirectX::BoundingBox* Box2 = object2->GetBounding()->GetBoundingBox();


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

	//押し出しをするかどうか
	if (object1->GetIsExtrusion())
	{
		Vector3 position = object1->GetPosition();

		position += pushBackVec;

		object1->SetPosition(position);
	}

	if (object2->GetIsExtrusion())
	{
		Vector3 position = object2->GetPosition();

		position -= pushBackVec;

		object2->SetPosition(position);
	}

}
