#include "pch.h"
#include "PlayerHead.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Animation.h"
#include "Game/CollisiionManager.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="parent">親</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
PlayerHead::PlayerHead(CommonResources* resources, 
	CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation)
	:
	PlayerPartsBase(resources, parent, PARTSNAME, scale, position, rotation)
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerHead::~PlayerHead()
{
}

/// <summary>
/// 初期化
/// </summary>
void PlayerHead::Initialize()
{

	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();


	//// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	//// モデルを読み込む
	auto model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/PlayerHead.cmo", *fx);

	PlayerPartsBase::SetModel(std::move(model));

	PlayerPartsBase::Initialize();

}

