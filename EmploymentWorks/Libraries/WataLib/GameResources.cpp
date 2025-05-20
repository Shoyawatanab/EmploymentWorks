#include "pch.h"
#include "GameResources.h"
#include <fstream>
#include "nlohmann/json.hpp"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/FMOD/inc/fmod.hpp"



// モデルのJsonファイル
const wchar_t* WataLib::GameResources::MODEL_JSON = L"Resources/Dates/ModelData.json";
// テクスチャのベースパス
const wchar_t* WataLib::GameResources::TEXTURE_BASE_PATH = L"Resources/Textures/";

// テクスチャのJsonファイル
const wchar_t* WataLib::GameResources::TEXTURE_JSON = L"Resources/Dates/TextureData.json";
// モデルのベースパス
const wchar_t* WataLib::GameResources::MODEL_BASE_PATH = L"Resources/Models/";



/// <summary>
/// コンテキスト
/// </summary>
/// <param name="device">デバイス</param>
WataLib::GameResources::GameResources(ID3D11Device1* device)
{
	// Jsonファイルを読み込んでモデルを生成する
	LoadModelFromJson(device);
	// テクスチャを読み込む
	LoadTexture(device);


}


/// <summary>
/// モデルの読み込み
/// </summary>
/// <param name="device">デバイス</param>
void WataLib::GameResources::LoadModelFromJson(ID3D11Device1* device)
{
	// Jsonファイルを開く
	std::ifstream ifs(MODEL_JSON);
	if (!ifs)
	{
		MessageBoxA(nullptr, "Jsonファイルが見つかりません", "エラー", MB_OK);
		return; // 処理を終了
	}

	// Jsonファイルを読み込む
	nlohmann::json json = nlohmann::json::parse(ifs);

	// Jsonデータを順に処理
	for (auto it = json.begin(); it != json.end(); ++it)
	{
		// キーと値を取得
		std::string key = it.key();
		std::string pathStr = it.value();

		// std::stringをstd::wstringに変換
		std::wstring path = MODEL_BASE_PATH + std::wstring(pathStr.begin(), pathStr.end());

		// モデルファクトリの生成
		std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
		fx->SetDirectory(L"Resources/Models");

		// モデルを生成
		auto model = DirectX::Model::CreateFromCMO(device, path.c_str(), *fx);

		// モデルをリストに追加
		m_modelList[key] = std::move(model);
	}

}

/// <summary>
/// 画像を読み込む
/// </summary>
/// <param name="device">デバイス</param>
void WataLib::GameResources::LoadTexture(ID3D11Device1* device)
{
	// Jsonファイルを開く
	std::ifstream ifs(TEXTURE_JSON);
	if (!ifs)
	{
		MessageBoxA(nullptr, "Jsonファイルが見つかりません", "エラー", MB_OK);
		return; // 処理を終了
	}

	// Jsonファイルを読み込む
	nlohmann::json json = nlohmann::json::parse(ifs);

	// Jsonデータを順に処理
	for (auto it = json.begin(); it != json.end(); ++it)
	{
		// キーと値を取得
		std::string key = it.key();
		std::string pathStr = it.value();

		// std::stringをstd::wstringに変換
		std::wstring path = TEXTURE_BASE_PATH + std::wstring(pathStr.begin(), pathStr.end());

		// テクスチャを生成
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

		DirectX::CreateWICTextureFromFileEx(
			device,
			path.c_str(),
			0,
			D3D11_USAGE_DEFAULT,
			D3D11_BIND_SHADER_RESOURCE,
			0,
			0,
			DirectX::WIC_LOADER_IGNORE_SRGB,
			nullptr,
			texture.GetAddressOf()
		);
		// テクスチャをリストに追加
		m_textureList[key] = texture;
	}
}

/// <summary>
/// モデルの取得
/// </summary>
/// <param name="key">キー</param>
/// <returns>モデル情報</returns>
DirectX::Model* WataLib::GameResources::GetModel(std::string key) const
{
	// キーを検索
	auto it = m_modelList.find(key);
	if (it != m_modelList.end())
	{
		// モデルを返す
		return it->second.get();
	}
	else
	{
		// エラーメッセージを表示
		MessageBoxA(nullptr, "モデルが見つかりません", "エラー", MB_OK);
		return nullptr;
	}
}

/// <summary>
/// 画像の取得
/// </summary>
/// <param name="key">キー</param>
/// <returns>画像情報</returns>
ID3D11ShaderResourceView* WataLib::GameResources::GetTexture(std::string key) const
{
	// キーを検索
	auto it = m_textureList.find(key);

	if (it != m_textureList.end())
	{
		// テクスチャを返す
		return it->second.Get();
	}
	else
	{
		// エラーメッセージを表示
		MessageBoxA(nullptr, "テクスチャが見つかりません", "エラー", MB_OK);
		return nullptr;
	}

}



