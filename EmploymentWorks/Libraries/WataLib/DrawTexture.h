/*
	@file	DrawTexture.h
	@brief	タイトルシーンクラス
*/
#pragma once


// 前方宣言
class CommonResources;


namespace WataLib
{
	class DrawTexture final
	{
	public:

		DirectX::SimpleMath::Vector2 GetPosition() { return m_position; }

		void SetPosition(DirectX::SimpleMath::Vector2 Pos) { m_position = Pos; }

		void SetScale(DirectX::SimpleMath::Vector2 scale) { m_scale = scale; }

		float GetRotate() { return m_rotate; }

		void SetRotate(float rotate) { m_rotate = rotate; }

		void SetEpansion(float expansion) { m_expansion = expansion; }

		void ResetExpansion() { m_expansion = 1.0f; }

		float GetWidth() { return m_width; }

		float GetHeight() { return m_height; }

		DirectX::SimpleMath::Vector2 GetInialPosition() { return m_inialPosition; }

		DirectX::SimpleMath::Vector2 GetInialScale() { return m_inialScale; }

		DirectX::SimpleMath::Vector2 GetCenter() { return m_texCenter; }


	public:
		DrawTexture();
		~DrawTexture();

		void Initialize(CommonResources* resources, const wchar_t* szFileName, DirectX::SimpleMath::Vector2 Pos, DirectX::SimpleMath::Vector2 scale);
		void Render();
		void Finalize();

	private:

		// 共通リソース
		CommonResources* m_commonResources;

		// スプライトバッチ
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

		//std::unique_ptr<DirectX::PrimitiveBatch> 

		// スプライトフォント
		std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

		// テクスチャ
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

		// テクスチャの半分の大きさ
		DirectX::SimpleMath::Vector2 m_texCenter;
		//画像の座標
		DirectX::SimpleMath::Vector2 m_position;
		//画像の大きさ
		DirectX::SimpleMath::Vector2 m_scale;
		//画像の回転角度
		float m_rotate;
		//拡大率
		float m_expansion;

		float m_width;
		float m_height;

		DirectX::SimpleMath::Vector2 m_inialPosition;
		DirectX::SimpleMath::Vector2 m_inialScale;


	};
}