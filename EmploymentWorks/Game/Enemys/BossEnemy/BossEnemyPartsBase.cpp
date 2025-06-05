#include "pch.h"
#include "BossEnemyPartsBase.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"

#include "Libraries/WataLib/Bounding.h"
#include "GameBase/Manager/CollisiionManager.h"
#include "Libraries/WataLib/Animation.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Params.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="root">ボス敵の根のクラス</param>
/// <param name="parent">親</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="partsName">パーツ名</param>
/// <param name="partsHP">パーツのＨＰ</param>
/// <param name="boxColliderSize">ボックスの当たり判定の大きさ</param>
/// <param name="SphereColliderSize">スフィアの当たり判定の大きさ</param>
BossEnemyPartsBase::BossEnemyPartsBase(CommonResources* resources
	, BossEnemy* root
	, CharacterEntity* parent
	, const DirectX::SimpleMath::Vector3& scale
	, const DirectX::SimpleMath::Vector3& position
	, const DirectX::SimpleMath::Quaternion& rotation
	, const std::string& partsName
	, const int partsHP
	, const DirectX::SimpleMath::Vector3& boxColliderSize
	, const float SphereColliderSize)
	:
	CompositeEntity(resources,scale,position,rotation)
{
	BaseEntity::SetParent(parent);
	BaseEntity::SetIsGravity(false);
}




/// <summary>
/// デストラクタ
/// </summary>
BossEnemyPartsBase::~BossEnemyPartsBase()
{
	
}


