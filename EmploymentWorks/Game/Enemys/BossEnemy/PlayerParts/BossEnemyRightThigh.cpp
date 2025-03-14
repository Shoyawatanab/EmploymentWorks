#include "pch.h"
#include "BossEnemyRightThigh.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Animation.h"

#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Bounding.h"

#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyRightLeg.h"
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
BossEnemyRightThigh::BossEnemyRightThigh(CommonResources* resources,
	BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,	DirectX::SimpleMath::Quaternion rotation)
	:
	BossEnemyPartsBase(resources, root, parent, scale, position, rotation, PARTSNAME, Params::BOSSENEMY_RIGHTTHIGH_HP,
		Params::BOSSENEMY_RIGHTTHIGH_BOX_COLLIDER_SIZE, Params::BOSSENEMY_RIGHTTHIGH_SPHERE_COLLIDER_SIZE)
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

	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();


	//// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	//// モデルを読み込む
	auto model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemyThigh.cmo", *fx);

	BossEnemyPartsBase::SetModel(std::move(model));

	BossEnemyPartsBase::Initialize();

	//「RightLeg」を生成する
	AddChild(std::make_unique<BossEnemyRightLeg>(BaseEntity::GetCommonResources(),
		BossEnemyPartsBase::GetRoot(),
		this,
		Params::BOSSENEMY_RIGHTLEG_SCALE,
		Params::BOSSENEMY_RIGHTLEG_POSITION,
		Params::BOSSENEMY_RIGHTLEG_ROTATION));

}




