#include "pch.h"
#include "BossEnemyRightShoulder.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Animation.h"
#include "Libraries/WataLib/GameResources.h"

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
		Params::BOSSENEMY_RIGHTSHOULDER_BOX_COLLIDER_SIZE * root->GetScale(), Params::BOSSENEMY_RIGHTSHOULDER_SPHERE_COLLIDER_SIZE * root->GetScale().x)
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
	//// モデルを読み込む
	auto model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BossEnemyShoulder");

	BossEnemyPartsBase::SetModel(model);

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




