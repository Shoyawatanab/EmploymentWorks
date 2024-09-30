#include "pch.h"
#include "Framework/Resources.h"
#include "DeviceResources.h"

std::unique_ptr<Resources> Resources::m_resources = nullptr;

// Resourcesクラスのインスタンスを取得する
Resources* const Resources::GetInstance()
{
	if (m_resources == nullptr)
	{
		// Resourcesクラスのインスタンスを生成する
		m_resources.reset(new Resources());
	}
	// Resourcesクラスのインスタンスを返す
	return m_resources.get();
}

// リソースをロードする
void Resources::LoadResource(CommonResources* resources)
{

	auto device = resources->GetDeviceResources()->GetD3DDevice();

	// リソースディレクトリを設定する
	std::unique_ptr<DirectX::EffectFactory> playerFx = std::make_unique<DirectX::EffectFactory>(device);
	playerFx->SetDirectory(L"Resources/Models");
	// 「プレイヤ」モデルをロードする
	m_playerModel = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Player.cmo", *playerFx);

	// リソースディレクトリを設定する
	std::unique_ptr<DirectX::EffectFactory> enemyFx = std::make_unique<DirectX::EffectFactory>(device);
	enemyFx->SetDirectory(L"Resources/Models");
	// 「敵」モデルをロードする
	m_enemyModel = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Enemy.cmo", *enemyFx);

	// リソースディレクトリを設定する
	std::unique_ptr<DirectX::EffectFactory> boomerangFx = std::make_unique<DirectX::EffectFactory>(device);
	boomerangFx->SetDirectory(L"Resources/Models");
	// 「ブーメラン」モデルをロードする
	m_boomerangModel = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Boomerang.cmo", *boomerangFx);

	// リソースディレクトリを設定する
	std::unique_ptr<DirectX::EffectFactory> floorFx = std::make_unique<DirectX::EffectFactory>(device);
	floorFx->SetDirectory(L"Resources/Models");
	// 「床」モデルをロードする
	m_floorModel = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Floor.cmo", *floorFx);

	// リソースディレクトリを設定する
	std::unique_ptr<DirectX::EffectFactory> skyFx = std::make_unique<DirectX::EffectFactory>(device);
	skyFx->SetDirectory(L"Resources/Models");
	// 「空」モデルをロードする
	m_skyModel = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Sky.cmo", *skyFx);

	// リソースディレクトリを設定する
	std::unique_ptr<DirectX::EffectFactory> tree1Fx = std::make_unique<DirectX::EffectFactory>(device);
	tree1Fx->SetDirectory(L"Resources/Models");
	// 「木１」モデルをロードする
	m_tree1Model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Tree1.cmo", *tree1Fx);

	// リソースディレクトリを設定する
	std::unique_ptr<DirectX::EffectFactory> rockFx = std::make_unique<DirectX::EffectFactory>(device);
	rockFx->SetDirectory(L"Resources/Models");
	// 「岩」モデルをロードする
	m_rockModel      = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Rock.cmo", *rockFx);



}
