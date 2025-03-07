#include "pch.h"
#include "BossEnemyRightShoulder.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Animation.h"

#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Bounding.h"

#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyRightArmJoint.h"
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
BossEnemyRightShoulder::BossEnemyRightShoulder(CommonResources* resources,
	BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,	DirectX::SimpleMath::Quaternion rotation)
	:
	BossEnemyPartsBase(resources, root, parent, scale, position, rotation, PARTSNAME, Params::BOSSENEMY_RIGHTSHOULDER_HP,
		Params::BOSSENEMY_RIGHTSHOULDER_BOX_COLLIDER_SIZE, Params::BOSSENEMY_RIGHTSHOULDER_SPHERE_COLLIDER_SIZE)
{
}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemyRightShoulder::~BossEnemyRightShoulder()
{
}

/// <summary>
/// 初期化
/// </summary>
void BossEnemyRightShoulder::Initialize()
{

	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();

	//// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	//// モデルを読み込む
	auto model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemyShoulder.cmo", *fx);

	BossEnemyPartsBase::SetModel(std::move(model));

	BossEnemyPartsBase::Initialize();

	//「RightArmJoint」を生成する
	AddChild(std::make_unique<BossEnemyRightArmJoint>(BaseEntity::GetCommonResources(),
		BossEnemyPartsBase::GetRoot(),
		this,
		Params::BOSSENEMY_RIGHTARMJOINT_SCALE,
		Params::BOSSENEMY_RIGHTARMJOINT_POSITION,
		Params::BOSSENEMY_RIGHTARMJOINT_ROTATION));



}

void BossEnemyRightShoulder::Update(const float& elapsedTime)
{

	BossEnemyPartsBase::Update(elapsedTime);

	BossEnemyPartsBase::GetRoot()->GetTarget();




}




