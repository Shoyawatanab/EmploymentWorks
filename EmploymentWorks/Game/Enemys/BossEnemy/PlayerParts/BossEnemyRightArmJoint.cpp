#include "pch.h"
#include "BossEnemyRightArmJoint.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Animation.h"

#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Bounding.h"

#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyRightArm.h"
#include "Game/Observer/Messenger.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Params.h"

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
BossEnemyRightArmJoint::BossEnemyRightArmJoint(CommonResources* resources,
	BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,	DirectX::SimpleMath::Quaternion rotation)
	:
	BossEnemyPartsBase(resources, root, parent, scale, position, rotation, PARTSNAME, Params::BOSSENEMY_RIGHTARMJOINT_HP,
		Params::BOSSENEMY_RIGHTARMJOINT_BOX_COLLIDER_SIZE, Params::BOSSENEMY_RIGHTARMJOINT_SPHERE_COLLIDER_SIZE)
{

}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemyRightArmJoint::~BossEnemyRightArmJoint()
{
}

/// <summary>
/// 初期化
/// </summary>
void BossEnemyRightArmJoint::Initialize()
{

	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();


	//// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	//// モデルを読み込む
	auto model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemyArmJoint.cmo", *fx);

	BossEnemyPartsBase::SetModel(std::move(model));

	BossEnemyPartsBase::Initialize();

	//「RightArm」を生成する
	AddChild(std::make_unique<BossEnemyRightArm>(BaseEntity::GetCommonResources(),
		BossEnemyPartsBase::GetRoot(),
		this,
		Params::BOSSENEMY_RIGHTARM_SCALE,
		Params::BOSSENEMY_RIGHTARM_POSITION,
		Params::BOSSENEMY_RIGHTARM_ROTATION));
}


