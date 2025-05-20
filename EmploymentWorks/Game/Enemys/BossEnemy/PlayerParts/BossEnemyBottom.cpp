#include "pch.h"
#include "BossEnemyBottom.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/GameResources.h"
#include "Libraries/WataLib/Animation.h"

#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Bounding.h"

#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyPelvis.h"
#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyLeftThigh.h"
#include"Game/Enemys/BossEnemy/PlayerParts/BossEnemyRightThigh.h"

#include "Game/Observer/Messenger.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
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
BossEnemyBottom::BossEnemyBottom(CommonResources* resources,BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,	DirectX::SimpleMath::Quaternion rotation)
	:
	BossEnemyPartsBase(resources, root,parent,scale,position,rotation, PARTSNAME, Params::BOSSENEMY_BODY_HP,
		Params::BOSSENEMY_BODY_BOX_COLLIDER_SIZE * root->GetScale(), Params::BOSSENEMY_BODY_SPHERE_COLLIDER_SIZE* root->GetScale().x)

{

}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemyBottom::~BossEnemyBottom()
{

}

/// <summary>
/// 初期化
/// </summary>
void BossEnemyBottom::Initialize()
{
	// モデルを読み込む
	auto model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BossEnemyBottom");

	BossEnemyPartsBase::SetModel(model);

	BossEnemyPartsBase::Initialize();

	//「Pelvis」を生成する
	BossEnemyPartsBase::AddChild(std::make_unique<BossEnemyPelvis>(BaseEntity::GetCommonResources(),
		BossEnemyPartsBase::GetRoot(),
		this,
		Params::BOSSENEMY_PELVIS_SCALE,
		Params::BOSSENEMY_PELVIS_POSITION,
		Params::BOSSENEMY_PELVIS_ROTATION));
	//「LeftThigh」を生成する
	BossEnemyPartsBase::AddChild(std::make_unique<BossEnemyLeftThigh>(BaseEntity::GetCommonResources(),
		BossEnemyPartsBase::GetRoot(),
		this,
		Params::BOSSENEMY_LEFTTHIGH_SCALE,
		Params::BOSSENEMY_LEFTTHIGH_POSITION,
		Params::BOSSENEMY_LEFTTHIGH_ROTATION));	
	//「RightThigh」を生成する
	BossEnemyPartsBase::AddChild(std::make_unique<BossEnemyRightThigh>(BaseEntity::GetCommonResources(),
		BossEnemyPartsBase::GetRoot(),
		this,
		Params::BOSSENEMY_RIGHTTHIGH_SCALE,
		Params::BOSSENEMY_RIGHTTHIGH_POSITION,
		Params::BOSSENEMY_RIGHTTHIGH_ROTATION));

}








