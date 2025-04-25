#pragma once
#include <unordered_map>


namespace FMOD
{
	class Sound;
	class System;
}



namespace WataLib
{

	class GameResources
	{
		// ------------------------
		// ファイルパス
		// ------------------------
	public:
		// モデルのJsonファイル
		static const wchar_t* MODEL_JSON;
		static const wchar_t* MODEL_BASE_PATH;

		// テクスチャのJsonファイル
		static const wchar_t* TEXTURE_JSON;
		static const wchar_t* TEXTURE_BASE_PATH;


		// ------------------------
		// アクセサ
		// ------------------------
	public:

		// モデルを取得する
		DirectX::Model* GetModel(std::string key) const;
		// テクスチャを取得する
		ID3D11ShaderResourceView* GetTexture(std::string key) const;

		FMOD::Sound* GetSound(std::string key) const;

		// ------------------------
		// 公開関数
		// ------------------------
	public:
		// コンストラクタ
		GameResources(ID3D11Device1* device);
		// デストラクタ
		~GameResources() = default;

		// ------------------------
		// 内部関数
		// ------------------------
	private:
		// Jsonファイルを読み込んでモデルを生成する
		void LoadModelFromJson(ID3D11Device1* device);

		// テクスチャを読み込む
		void LoadTexture(ID3D11Device1* device);


		// ------------------------
		// 内部変数
		// ------------------------
	private:

		// リソース
		static std::unique_ptr<WataLib::GameResources> m_resources;

		// モデルリスト
		std::unordered_map<std::string, std::unique_ptr<DirectX::Model>> m_modelList;

		// テクスチャリスト
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textureList;

		std::unordered_map<std::string, FMOD::Sound*> m_soundList;



	};
}