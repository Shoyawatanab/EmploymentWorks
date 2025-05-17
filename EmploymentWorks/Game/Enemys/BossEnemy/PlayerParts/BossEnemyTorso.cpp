#include "pch.h"
#include "BossEnemyTorso.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Animation.h"
#include "Libraries/WataLib/GameResources.h"

#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Bounding.h"

#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyHead.h"
#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyLeftShoulder.h"
#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyRightShoulder.h"

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
BossEnemyTorso::BossEnemyTorso(CommonResources* resources,BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,	DirectX::SimpleMath::Quaternion rotation)
	:
	BossEnemyPartsBase(resources, root, parent, scale, position, rotation, PARTSNAME, Params::BOSSENEMY_TORSO_HP,
		Params::BOSSENEMY_TORSO_BOX_COLLIDER_SIZE * root->GetScale(), Params::BOSSENEMY_TORSO_SPHERE_COLLIDER_SIZE * root->GetScale().x)
{

}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemyTorso::~BossEnemyTorso()
{
}

/// <summary>
/// 初期化
/// </summary>
void BossEnemyTorso::Initialize()
{

	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();


	//// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	//// モデルを読み込む
	auto model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BossEnemyTorso");

	BossEnemyPartsBase::SetModel(model);

	BossEnemyPartsBase::Initialize();

	//「Head」を生成する
	AddChild(std::make_unique<BossEnemyHead>(BaseEntity::GetCommonResources(),
		BossEnemyPartsBase::GetRoot(),
		this,
		Params::BOSSENEMY_HEAD_SCALE,
		Params::BOSSENEMY_HEAD_POSITION,
		Params::BOSSENEMY_HEAD_ROTATION));
	//「LeftShouder」を生成する
	AddChild(std::make_unique<BossEnemyLeftShoulder>(BaseEntity::GetCommonResources(),
		BossEnemyPartsBase::GetRoot(),
		this,
		Params::BOSSENEMY_LEFTSHOULDER_SCALE,
		Params::BOSSENEMY_LEFTSHOULDER_POSITION,
		Params::BOSSENEMY_LEFTSHOULDER_ROTATION));
	//「RightShouder」を生成する
	AddChild(std::make_unique<BossEnemyRightShoulder>(BaseEntity::GetCommonResources(),
		BossEnemyPartsBase::GetRoot(),
		this,
		Params::BOSSENEMY_RIGHTSHOULDER_SCALE,
		Params::BOSSENEMY_RIGHTSHOULDER_POSITION,
		Params::BOSSENEMY_RIGHTSHOULDER_ROTATION));

}





