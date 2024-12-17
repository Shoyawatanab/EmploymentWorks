#pragma once
#ifndef ICollisionObject_DEFINED
#define ICollisionObject_DEFINED

class CollisionManager;
class Bounding;

static const uint32_t bit = 1 << 0;


enum  class CollsionObjectTag
{

	None = 0
	, Player = 1 << 0     //プレイヤ
	, Enemy = 1 << 1     //敵
	, Boomerang = 1 << 2     //ブーメラン
	, Stage = 1 << 3     //床以外のステージオブジェック　壁や天井
	, Floor = 1 << 4     //床
	, Pillar = 1 << 5     //柱
	, Artillery = 1 << 6     //砲台
	, ArtilleryBullet = 1 << 7     //砲台の弾
	, EnemyParts = 1 << 8     //敵の部品
	, Beam = 1 << 9

};


//当たり判定の種類 ORで判定する
enum class CollisionType
{

	Player_Enemy = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Enemy)
	, Player_Boomerang = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Boomerang)
	, Player_Stage = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Stage)
	, Player_Floor = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Floor)
	, Player_Pillar = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Pillar)
	, Player_Artillery = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Artillery)
	, Player_ArtilleryBullet = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::ArtilleryBullet)

	, Enemy_Boomerang = static_cast<uint32_t>(CollsionObjectTag::Enemy) | static_cast<uint32_t>(CollsionObjectTag::Boomerang)
	, Enemy_Stage = static_cast<uint32_t>(CollsionObjectTag::Enemy) | static_cast<uint32_t>(CollsionObjectTag::Stage)
	, Enemy_Floor = static_cast<uint32_t>(CollsionObjectTag::Enemy) | static_cast<uint32_t>(CollsionObjectTag::Floor)
	, Enemy_Pillar = static_cast<uint32_t>(CollsionObjectTag::Enemy) | static_cast<uint32_t>(CollsionObjectTag::Pillar)
	, Enemy_Artillery = static_cast<uint32_t>(CollsionObjectTag::Enemy) | static_cast<uint32_t>(CollsionObjectTag::Artillery)
	, Enemy_ArtilleryBullet = static_cast<uint32_t>(CollsionObjectTag::Enemy) | static_cast<uint32_t>(CollsionObjectTag::ArtilleryBullet)

	, Boomerang_Stage = static_cast<uint32_t>(CollsionObjectTag::Boomerang) | static_cast<uint32_t>(CollsionObjectTag::Stage)
	, Boomerang_Floor = static_cast<uint32_t>(CollsionObjectTag::Boomerang) | static_cast<uint32_t>(CollsionObjectTag::Floor)
	, Boomerang_Pillar = static_cast<uint32_t>(CollsionObjectTag::Boomerang) | static_cast<uint32_t>(CollsionObjectTag::Pillar)
	, Boomerang_Artillery = static_cast<uint32_t>(CollsionObjectTag::Boomerang) | static_cast<uint32_t>(CollsionObjectTag::Artillery)
	, Boomerang_ArtilleryBullet = static_cast<uint32_t>(CollsionObjectTag::Boomerang) | static_cast<uint32_t>(CollsionObjectTag::ArtilleryBullet)

	, ArtilleryBullet_Stage = static_cast<uint32_t>(CollsionObjectTag::ArtilleryBullet) | static_cast<uint32_t>(CollsionObjectTag::Stage)


	,EnemyParts_Boomerang = static_cast<uint32_t>(CollsionObjectTag::EnemyParts) | static_cast<uint32_t>(CollsionObjectTag::Boomerang)

	,Beam_Player = static_cast<uint32_t>(CollsionObjectTag::Beam) | static_cast<uint32_t>(CollsionObjectTag::Player)
	,Beam_Floor = static_cast<uint32_t>(CollsionObjectTag::Beam) | static_cast<uint32_t>(CollsionObjectTag::Floor)

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

	virtual void SetPosition(DirectX::SimpleMath::Vector3& Pos) = 0;

	virtual DirectX::SimpleMath::Vector3 GetPosition() = 0;

	////何かと当たった時に継続的に呼ばれるUpdate
	//virtual void OnCollisionUpdate(float elapsdTime) = 0;

};

#endif		// ICollisionObject_DEFINED
