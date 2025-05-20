#include "pch.h"
#include "PlayerRightArm.h"
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
PlayerRightArm::PlayerRightArm(CommonResources* resources, 
	CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation)
	:
	PlayerPartsBase(resources, parent, PARTSNAME, scale, position, rotation)

{

}

/// <summary>
/// デストラクタ
/// </summary>
PlayerRightArm::~PlayerRightArm()
{
}

/// <summary>
/// 初期化
/// </summary>
void PlayerRightArm::Initialize()
{



	//// モデルを読み込む
	auto model = PlayerPartsBase::GetCommonResources()->GetGameResources()->GetModel("PlayerArm");

	PlayerPartsBase::SetModel(model);

	PlayerPartsBase::Initialize();



}



