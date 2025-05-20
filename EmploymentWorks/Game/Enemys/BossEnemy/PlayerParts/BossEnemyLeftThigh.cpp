#include "pch.h"
#include "BossEnemyLeftThigh.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Animation.h"
#include "Libraries/WataLib/GameResources.h"

#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Bounding.h"

#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyLeftLeg.h"
#include "Game/Observer/Messenger.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Params.h"
#include "Game/Enemys/BossEnemy/BossEnemy.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="root">ボス敵の根のクラス</param>
/// <param name="parent">親</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
BossEnemyLeftThigh::BossEnemyLeftThigh(CommonResources* resources,
	BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,	DirectX::SimpleMath::Quaternion rotation)
	:
	BossEnemyPartsBase(resources, root, parent, scale, position, rotation, PARTSNAME, Params::BOSSENEMY_LEFTTHIGH_HP,
		Params::BOSSENEMY_LEFTTHIGH_BOX_COLLIDER_SIZE * root->GetScale(), Params::BOSSENEMY_LEFTTHIGH_SPHERE_COLLIDER_SIZE * root->GetScale().x)
{

}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemyLeftThigh::~BossEnemyLeftThigh()
{
}

/// <summary>
/// 初期化
/// </summary>
void BossEnemyLeftThigh::Initialize()
{
	//// モデルを読み込む
	auto model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BossEnemyThigh");

	BossEnemyPartsBase::SetModel(model);


	BossEnemyPartsBase::Initialize();

	//「LeftLeg」を生成する
	AddChild(std::make_unique<BossEnemyLeftLeg>(BaseEntity::GetCommonResources(),
		BossEnemyPartsBase::GetRoot(),
		this,
		Params::BOSSENEMY_LEFTLEG_SCALE,
		Params::BOSSENEMY_LEFTLEG_POSITION,
		Params::BOSSENEMY_LEFTLEG_ROTATION));
}




