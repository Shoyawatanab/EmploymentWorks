#include "pch.h"
#include "BossEnemyRightArm.h"
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
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Enemys/BossEnemy/BossEnemy.h"
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
BossEnemyRightArm::BossEnemyRightArm(CommonResources* resources,BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,	DirectX::SimpleMath::Quaternion rotation)
	:
	BossEnemyPartsBase(resources, root, parent, scale, position, rotation, PARTSNAME, Params::BOSSENEMY_RIGHTARM_HP,
		Params::BOSSENEMY_RIGHTARM_BOX_COLLIDER_SIZE * root->GetScale(), Params::BOSSENEMY_RIGHTARM_SPHERE_COLLIDER_SIZE * root->GetScale().x)
{
}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemyRightArm::~BossEnemyRightArm()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void BossEnemyRightArm::Initialize()
{

	//// モデルを読み込む
	auto model =BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BossEnemyArm");

	BossEnemyPartsBase::SetModel(model);

	BossEnemyPartsBase::Initialize();
}


/// <summary>
/// 当たった時に呼び出される関数
/// </summary>
/// <param name="object">相手のオブジェクト</param>
/// <param name="tag">相手のタグ</param>
void BossEnemyRightArm::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	switch (tag)
	{
		case CollisionEntity::CollisionTag::STAGE:
		{

			//パーティクルの生成のメッセージを送る
			Vector3 pos = BaseEntity::GetPosition();
			pos.y = 0;
			Messenger::GetInstance()->Notify(GameMessageType::CREATE_PARTICLE, &pos);
		}
		break;
		default:
			break;
	}


	BossEnemyPartsBase::OnCollisionEnter(object, tag);


}


