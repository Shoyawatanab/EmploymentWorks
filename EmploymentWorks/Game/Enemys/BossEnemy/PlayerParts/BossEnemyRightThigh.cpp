#include "pch.h"
#include "BossEnemyRightThigh.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Animation.h"
#include "Libraries/WataLib/GameResources.h"

#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Bounding.h"

#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyRightLeg.h"
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
BossEnemyRightThigh::BossEnemyRightThigh(CommonResources* resources,
	BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,	DirectX::SimpleMath::Quaternion rotation)
	:
	BossEnemyPartsBase(resources, root, parent, scale, position, rotation, PARTSNAME, Params::BOSSENEMY_RIGHTTHIGH_HP,
		Params::BOSSENEMY_RIGHTTHIGH_BOX_COLLIDER_SIZE * root->GetScale(), Params::BOSSENEMY_RIGHTTHIGH_SPHERE_COLLIDER_SIZE * root->GetScale().x)
{

}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemyRightThigh::~BossEnemyRightThigh()
{
}

/// <summary>
/// 初期化
/// </summary>
void BossEnemyRightThigh::Initialize()
{

	//// モデルを読み込む
	auto model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BossEnemyThigh");

	BossEnemyPartsBase::SetModel(model);

	BossEnemyPartsBase::Initialize();

	//「RightLeg」を生成する
	AddChild(std::make_unique<BossEnemyRightLeg>(BaseEntity::GetCommonResources(),
		BossEnemyPartsBase::GetRoot(),
		this,
		Params::BOSSENEMY_RIGHTLEG_SCALE,
		Params::BOSSENEMY_RIGHTLEG_POSITION,
		Params::BOSSENEMY_RIGHTLEG_ROTATION));

}




