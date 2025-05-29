#include "pch.h"
#include "PlayerLeftFeet.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/GameResources.h"

#include "Libraries/WataLib/Animation.h"
#include "Game/CollisiionManager.h"




/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="parent">親</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
PlayerLeftFeet::PlayerLeftFeet(CommonResources* resources 
	, CharacterEntity* parent
	, const DirectX::SimpleMath::Vector3& scale
	, const DirectX::SimpleMath::Vector3& position
	, const DirectX::SimpleMath::Quaternion& rotation)
:
	PlayerPartsBase(resources, parent, PARTSNAME, scale, position, rotation)

{

}

/// <summary>
/// デストラクタ
/// </summary>
PlayerLeftFeet::~PlayerLeftFeet()
{
}

/// <summary>
/// 初期化
/// </summary>
void PlayerLeftFeet::Initialize()
{

	//// モデルを読み込む
	auto model = PlayerPartsBase::GetCommonResources()->GetGameResources()->GetModel("PlayerFeet");

	PlayerPartsBase::SetModel(model);

	PlayerPartsBase::Initialize();


}

