/*
	@file	Texture.h
	@brief	タイトルシーンクラス
*/
#pragma once


// 前方宣言
class CommonResources;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}

namespace mylib
{
	class Texture final
	{
	public:

		void SetPosition(DirectX::SimpleMath::Vector2 Pos) { m_position = Pos; }

		void SetScale(float scale) { m_scale = scale; }

		float GetRotate() { return m_rotate; }

		void SetRotate(float rotate) { m_rotate = rotate; }

	private:

		// 共通リソース
		CommonResources* m_commonResources;

		// スプライトバッチ
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

		// スプライトフォント
		std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

		// テクスチャ
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

		// テクスチャの半分の大きさ
		DirectX::SimpleMath::Vector2 m_texCenter;
		//画像の座標
		DirectX::SimpleMath::Vector2 m_position;
		//画像の大きさ
		float m_scale;
		//画像の回転角度
		float m_rotate;

	public:
		Texture();
		~Texture();

		void Initialize(CommonResources* resources, const wchar_t* szFileName, DirectX::SimpleMath::Vector2 Pos, float scale);
		void Render();
		void Finalize();



	};
}