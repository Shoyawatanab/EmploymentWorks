#include "pch.h"
#include "BossEnemyLeftArm.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Animation.h"
#include "Libraries/WataLib/GameResources.h"

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
BossEnemyLeftArm::BossEnemyLeftArm(CommonResources* resources,
	BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,	DirectX::SimpleMath::Quaternion rotation)
	:
	BossEnemyPartsBase(resources, root, parent, scale, position, rotation, PARTSNAME, Params::BOSSENEMY_LEFTARM_HP,
		Params::BOSSENEMY_LEFTARM_BOX_COLLIDER_SIZE * root->GetScale(), Params::BOSSENEMY_LEFTARM_SPHERE_COLLIDER_SIZE * root->GetScale().x)
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

	//// モデルを読み込む
	auto model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BossEnemyArm");

	BossEnemyPartsBase::SetModel(model);


	BossEnemyPartsBase::Initialize();
}




void BossEnemyLeftArm::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	BossEnemyPartsBase::OnCollisionEnter(object, tag);

	switch (tag)
	{
		case CollisionEntity::CollisionTag::Stage:
		{
			if(BossEnemyPartsBase::GetPartsHP() > 0)
			{
				Vector3	pos = BaseEntity::GetPosition();


				pos.y = 0;



				Messenger::GetInstance()->Notify(GameMessageType::CreateParticle, &pos);

			}
			else 
			{
				Vector3 scale = BaseEntity::GetScale() * 3;
				Vector3 position = BaseEntity::GetPosition();
				UnknownDataTwo aa = { static_cast<void*>(&position) ,static_cast<void*>(&scale) };

				Messenger::GetInstance()->Notify(GameMessageType::CreateExplosion, &aa);

				float power = 0.1f;

				Messenger::GetInstance()->Notify(GameMessageType::CameraShake, &power);

			}
		}
			break;
		case CollisionTag::Boomerang:
			if (BossEnemyPartsBase::GetPartsHP() <= 0)
			{
				BaseEntity::SetParent(nullptr);
				BaseEntity::SetIsGravity(true);
			}

			break;

		default:
			break;
	}


	BossEnemyPartsBase::OnCollisionEnter(object, tag);

}


