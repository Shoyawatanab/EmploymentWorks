/*
	@file	DamageCountUI.h
	@brief	タイトルシーンクラス
*/
#pragma once


// 前方宣言
class CommonResources;
class UserInterface;
class DrawNumber;


namespace WataLib
{
	class DamageCountUI final
	{
	public:
		//文字間隔
		static constexpr float DIGITWIDTH = 4.5f;
		//生成時間
		static constexpr float MAXTIME = 1.0f;

	public:

		DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }

		void SetPosition(DirectX::SimpleMath::Vector3 Pos);

		void SetScale(DirectX::SimpleMath::Vector2 scale);

		float GetRotate() { return m_rotate; }

		void SetRotate(float rotate);

		DirectX::SimpleMath::Vector2 GetCenter() { return m_texCenter; }

		void SetDamage(int damage);

		void SetScreenPosition(DirectX::SimpleMath::Vector2 position);

		void SetIsActive(bool isActive) { m_isActive = isActive; }

		bool GetIsActive() { return m_isActive; }
		
	public:
		DamageCountUI(CommonResources* resources);
		~DamageCountUI();

		void Initialize();

		// 更新する
		void Update(const float& elapsedTime);

		void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

		void Finalize();

	private:

		//画像の読み込み
		std::unique_ptr<UserInterface> LoadTexture(const wchar_t* path
			, DirectX::SimpleMath::Vector2 position
			, DirectX::SimpleMath::Vector2 scale
		);

		DirectX::SimpleMath::Vector2 WorldToScreen(const DirectX::SimpleMath::Vector3& worldPos,
			const DirectX::SimpleMath::Matrix& worldMatrix,
			const DirectX::SimpleMath::Matrix& viewMatrix,
			const DirectX::SimpleMath::Matrix& projectionMatrix,
			int screenWidth, int screenHeight);


	private:
		// 共通リソース
		CommonResources* m_commonResources;
		// テクスチャ
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
		// テクスチャの半分の大きさ
		DirectX::SimpleMath::Vector2 m_texCenter;
		//画像の座標
		DirectX::SimpleMath::Vector3 m_position;
		//画像の大きさ
		DirectX::SimpleMath::Vector2 m_scale;
		//画像の回転角度
		float m_rotate;
		//背景
		std::unique_ptr<UserInterface> m_backGraund;
		//
		std::unique_ptr<DrawNumber> m_numberUI;
		//ダメージ
		int m_damage;
		//スクリーン座標
		DirectX::SimpleMath::Vector2 m_screenPosition;
		//
		bool m_isActive;

		//1桁目
		std::vector<std::pair<int,DirectX::SimpleMath::Vector2>> m_digitNumber;
		//時間
		float m_time;

	};
}