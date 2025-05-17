#include "pch.h"
#include "BossEnemyPelvis.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Animation.h"
#include "Libraries/WataLib/GameResources.h"

#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Bounding.h"

#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyTorso.h"
#include "Game/Observer/Messenger.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Params.h"
#include "Game/Enemys/BossEnemy/BossEnemy.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="root">ボス敵の根のクラス</param>
/// <param name="parent">親</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
BossEnemyPelvis::BossEnemyPelvis(CommonResources* resources
	,BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,	DirectX::SimpleMath::Quaternion rotation)
	:
	BossEnemyPartsBase(resources, root, parent, scale, position, rotation, PARTSNAME, Params::BOSSENEMY_PELVIS_HP,
		Params::BOSSENEMY_PELVIS_BOX_COLLIDER_SIZE * root->GetScale(), Params::BOSSENEMY_PELVIS_SPHERE_COLLIDER_SIZE * root->GetScale().x)
{
}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemyPelvis::~BossEnemyPelvis()
{
}

/// <summary>
/// 初期化
/// </summary>
void BossEnemyPelvis::Initialize()
{

	//// モデルを読み込む
	auto model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BossEnemyPelvis");

	BossEnemyPartsBase::SetModel(model);


	BossEnemyPartsBase::Initialize();

	////「Torso」を生成する
	AddChild(std::make_unique<BossEnemyTorso>(BaseEntity::GetCommonResources(),
		BossEnemyPartsBase::GetRoot(),
		this,
		Params::BOSSENEMY_TORSO_SCALE,
		Params::BOSSENEMY_TORSO_POSITION,
		Params::BOSSENEMY_TORSO_ROTATION));

}



