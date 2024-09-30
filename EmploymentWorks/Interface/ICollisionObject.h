#pragma once
#ifndef ICollisionObject_DEFINED
#define ICollisionObject_DEFINED

class CollisionManager;
class Bounding;

namespace  mylib
{
	class CollisionMesh;

}

static const uint32_t bit = 1 << 0;


enum  class CollsionObjectTag
{

	None = 0
	, Player = 1 << 0
	, Enemy = 1 << 1
	, Boomerang = 1 << 2
	, Floor = 1 << 3     //ステージの床と壁以外の動かないオブジェクト
	, Rock = 1 << 4
	, Tree1 = 1 << 5
};

//当たり判定の種類 ORで判定する
enum class CollisionType
{

	Player_Enemy = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Enemy)

	, Player_Boomerang = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Boomerang)
	, Enemy_Boomerang = static_cast<uint32_t>(CollsionObjectTag::Enemy) | static_cast<uint32_t>(CollsionObjectTag::Boomerang)

	, Player_Floor = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Floor)
	, Enemy_Floor = static_cast<uint32_t>(CollsionObjectTag::Enemy) | static_cast<uint32_t>(CollsionObjectTag::Floor)
	, Boomerang_Floor = static_cast<uint32_t>(CollsionObjectTag::Boomerang) | static_cast<uint32_t>(CollsionObjectTag::Floor)

	, Player_Rock = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Rock)
	, Enemy_Rock = static_cast<uint32_t>(CollsionObjectTag::Enemy) | static_cast<uint32_t>(CollsionObjectTag::Rock)
	, Boomerang_Rock = static_cast<uint32_t>(CollsionObjectTag::Boomerang) | static_cast<uint32_t>(CollsionObjectTag::Rock)
	, Floor_Rock = static_cast<uint32_t>(CollsionObjectTag::Floor) | static_cast<uint32_t>(CollsionObjectTag::Rock)

	, Player_Tree1 = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Tree1)
	, Enemy_Tree1 = static_cast<uint32_t>(CollsionObjectTag::Enemy) | static_cast<uint32_t>(CollsionObjectTag::Tree1)
	, Boomerang_Tree1 = static_cast<uint32_t>(CollsionObjectTag::Boomerang) | static_cast<uint32_t>(CollsionObjectTag::Tree1)
	, Floor_Tree1 = static_cast<uint32_t>(CollsionObjectTag::Floor) | static_cast<uint32_t>(CollsionObjectTag::Tree1)
	, Rock_Tree1 = static_cast<uint32_t>(CollsionObjectTag::Rock) | static_cast<uint32_t>(CollsionObjectTag::Tree1)


};


// ICollisionObjectインタフェースを定義する(GOF Stateパターン)
class ICollisionObject
{
public:
	/// <summary>
	/// 当たり判定クラスに登録する
	/// </summary>
	/// <param name="collsionManager">当たり判定クラス</param>
	virtual void RegistrationCollionManager(CollisionManager* collsionManager) = 0;


	/// <summary>
	/// バウンディングクラスの取得
	/// </summary>
	/// <returns>バウンディングクラス</returns>
	virtual Bounding* GetBounding() const = 0;


	/// <summary>
	/// タグの取得
	/// </summary>
	/// <returns>タグ</returns>
	virtual CollsionObjectTag GetCollsionTag() const = 0;

	/// <summary>
	/// 当たった時に呼び出す関数
	/// </summary>
	/// <param name="tag">当たった時の相手のタグ</param>
	virtual void OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos1) = 0;

	virtual void SetPos(DirectX::SimpleMath::Vector3& Pos) = 0;

	virtual DirectX::SimpleMath::Vector3 GetPos() = 0;

	////何かと当たった時に継続的に呼ばれるUpdate
	//virtual void OnCollisionUpdate(float elapsdTime) = 0;


	virtual mylib::CollisionMesh* GetCollsionMesh() = 0;
};

#endif		// ICollisionObject_DEFINED
