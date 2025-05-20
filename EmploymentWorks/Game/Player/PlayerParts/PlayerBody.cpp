#include "pch.h"
#include "PlayerBody.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/GameResources.h"
#include "Libraries/WataLib/Animation.h"

#include "Game/Player/PlayerParts/PlayerHead.h"
#include "Game/Player/PlayerParts/PlayerLeftArm.h"
#include "Game/Player/PlayerParts/PlayerRightArm.h"
#include "Game/Player/PlayerParts/PlayerLeftFeet.h"
#include "Game/Player/PlayerParts/PlayerRightFeet.h"
#include "Game/CollisiionManager.h"
#include "Game/Params.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="parent">親</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
PlayerBody::PlayerBody(CommonResources* resources
	,CharacterEntity* parent
	, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position
	,DirectX::SimpleMath::Quaternion rotation)
	:
	PlayerPartsBase(resources, parent ,PARTSNAME,scale,position,rotation)
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerBody::~PlayerBody()
{
}

/// <summary>
/// 初期化
/// </summary>
void PlayerBody::Initialize()
{


	//// モデルを読み込む準備
	auto model = PlayerPartsBase::GetCommonResources()->GetGameResources()->GetModel("PlayerBody");

	PlayerPartsBase::SetModel(model);

	PlayerPartsBase::Initialize();

	//「Head」を生成する
	AddChild(std::make_unique<PlayerHead>(BaseEntity::GetCommonResources(),
		this, 
		Params::PLAYER_HEAD_SCALE, 
		Params::PLAYER_HEAD_POSITION,
		Params::PLAYER_HEAD_ROTATION));
	//「LeftArm」を生成する
	AddChild(std::make_unique<PlayerLeftArm>(BaseEntity::GetCommonResources(),
		this,
		Params::PLAYER_LEFRARM_SCALE,
		Params::PLAYER_LEFRARM_POSITION,
		Params::PLAYER_LEFRARM_ROTATION));

	//「RightArm」を生成する
	AddChild(std::make_unique<PlayerRightArm>(BaseEntity::GetCommonResources(),
		this,
		Params::PLAYER_RIGHTARM_SCALE,
		Params::PLAYER_RIGHTARM_POSITION,
		Params::PLAYER_RIGHTARM_ROTATION));

	//「LeftFeet」を生成する
	AddChild(std::make_unique<PlayerLeftFeet>(BaseEntity::GetCommonResources(),
		this,
		Params::PLAYER_LEFRFEET_SCALE,
		Params::PLAYER_LEFRFEET_POSITION,
		Params::PLAYER_LEFRFEET_ROTATION));

	//「RightFeet」を生成する
	AddChild(std::make_unique<PlayerRightFeet>(BaseEntity::GetCommonResources(),
		this, 
		Params::PLAYER_RIGHTFEET_SCALE, 
		Params::PLAYER_RIGHTFEET_POSITION,
		Params::PLAYER_RIGHTFEET_ROTATION));


}

