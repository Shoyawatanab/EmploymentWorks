#include "pch.h"
#include "BossEnemyLeftArm.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Animation.h"

#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Bounding.h"

#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyPelvis.h"
#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyLeftThigh.h"
#include"Game/Enemys/BossEnemy/PlayerParts/BossEnemyRightThigh.h"
#include "Game/Observer/Messenger.h"

#include "Game/Interface/ICollisionObject.h"
#include "Game/Observer/Messenger.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Enemys/BossEnemy/BossEnemy.h"
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
BossEnemyLeftArm::BossEnemyLeftArm(CommonResources* resources,
	BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,	DirectX::SimpleMath::Quaternion rotation)
	:
	BossEnemyPartsBase(resources, root, parent, scale, position, rotation, PARTSNAME, Params::BOSSENEMY_LEFTARM_HP,
		Params::BOSSENEMY_LEFTARM_BOX_COLLIDER_SIZE, Params::BOSSENEMY_LEFTARM_SPHERE_COLLIDER_SIZE)
{
}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemyLeftArm::~BossEnemyLeftArm()
{
}

/// <summary>
/// 初期化
/// </summary>
void BossEnemyLeftArm::Initialize()
{

	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();


	//// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	//// モデルを読み込む
	auto model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemyArm.cmo", *fx);

	BossEnemyPartsBase::SetModel(std::move(model));


	BossEnemyPartsBase::Initialize();
}




void BossEnemyLeftArm::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{


	switch (tag)
	{
		case CollisionEntity::CollisionTag::Stage:
		{

			DirectX::SimpleMath::Vector3 pos = Vector3(2.5f, -3, 2);

			pos = Vector3::Transform(pos, BossEnemyPartsBase::GetRoot()->GetRotation());

			EventParams::CreateParticleDatas aaa = { pos  + BossEnemyPartsBase::GetRoot()->GetPosition()};

			

			Messenger::Notify(EventParams::EventType::CreateParticle, &aaa);
		}
			break;
		default:
			break;
	}


	BossEnemyPartsBase::OnCollisionEnter(object, tag);

}


