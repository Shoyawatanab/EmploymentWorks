#include "pch.h"
#include "BossEnemyLeftShoulder.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Animation.h"
#include "Libraries/WataLib/GameResources.h"

#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Bounding.h"

#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyLeftArmJoint.h"
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
BossEnemyLeftShoulder::BossEnemyLeftShoulder(CommonResources* resources,
	BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,	DirectX::SimpleMath::Quaternion rotation)
	:
	BossEnemyPartsBase(resources, root, parent, scale, position, rotation, PARTSNAME, Params::BOSSENEMY_LEFTSHOULDER_HP,
		Params::BOSSENEMY_LEFTSHOULDER_BOX_COLLIDER_SIZE, Params::BOSSENEMY_LEFTSHOULDER_SPHERE_COLLIDER_SIZE)
{

}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemyLeftShoulder::~BossEnemyLeftShoulder()
{
}


/// <summary>
/// 初期化
/// </summary>
void BossEnemyLeftShoulder::Initialize()
{
	
	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();

	//// モデルを読み込む
	auto model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BossEnemyShoulder");

	BossEnemyPartsBase::SetModel(model);


	BossEnemyPartsBase::Initialize();
	//「LeftArmJoint」を生成する
	AddChild(std::make_unique<BossEnemyLeftArmJoint>(BaseEntity::GetCommonResources(),
		BossEnemyPartsBase::GetRoot(),
		this,
		Params::BOSSENEMY_LEFTARMJOINT_SCALE,
		Params::BOSSENEMY_LEFTARMJOINT_POSITION,
		Params::BOSSENEMY_LEFTARMJOINT_ROTATION));


}





