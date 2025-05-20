#include "pch.h"
#include "BossEnemyLeftLeg.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Animation.h"
#include "Libraries/WataLib/GameResources.h"

#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Bounding.h"

#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyPelvis.h"

#include "Game/Observer/Messenger.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
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
BossEnemyLeftLeg::BossEnemyLeftLeg(CommonResources* resources,BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,	DirectX::SimpleMath::Quaternion rotation)
	:
	BossEnemyPartsBase(resources, root, parent, scale, position, rotation, PARTSNAME, Params::BOSSENEMY_LEFTLEG_HP,
		Params::BOSSENEMY_LEFTLEG_BOX_COLLIDER_SIZE * root->GetScale(), Params::BOSSENEMY_LEFTLEG_SPHERE_COLLIDER_SIZE * root->GetScale().x)
{

}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemyLeftLeg::~BossEnemyLeftLeg()
{
}

/// <summary>
/// 初期化
/// </summary>
void BossEnemyLeftLeg::Initialize()
{

	//// モデルを読み込む
	auto model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BossEnemyLeg");

	BossEnemyPartsBase::SetModel(model);


	BossEnemyPartsBase::Initialize();


}




