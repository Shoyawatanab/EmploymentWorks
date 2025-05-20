/*
	@file	ExplosionEffects.h
	@brief	一般的なシーンクラス
*/
#pragma once
#include "Game/Interface/IEffect.h"

// 前方宣言
class CommonResources;


class ExplosionEffects : public IEffect
{
private:

	static constexpr DirectX::SimpleMath::Vector2 SCALE {2, 2};

	// アニメーションサイズ
	static constexpr float ANIMATION_SIZE = 1.0f / 7.0f;	// 7枚
	// アニメーションのインターバル：フレーム単位
	static constexpr int ANIMATION_INTERVAL = 5;


public:

	//オブジェクトが有効か
	bool GetIsActive() override { return m_isActive; };
	//オブジェクトが有効かの登録
	void SetIsActive(bool isActive) override { m_isActive = isActive; };
	//座標の登録
	void SetPosition(DirectX::SimpleMath::Vector3 position) override { m_position = position; };
	//大きさの登録
	void SetScale(DirectX::SimpleMath::Vector3 scale) override { m_scale = scale; };
	//エフェクトの種類のタグ
	EffectType GetEffectType()  override { return EffectType::EXPLOSION; };




//継承関係
public:
	//コンストラクタ
	ExplosionEffects(CommonResources* resources);
	//デストラクタ
	~ExplosionEffects() override;
	//初期化
	void Initialize() override;
	//更新処理
	void Update(const float& elapsedTime) override;
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const  DirectX::SimpleMath::Matrix& proj) override;

private:
	//エフェクトの生成
	void Create(void* datas) override ;

private:

	// 共通リソース
	CommonResources* m_commonResources;
	//オブジェクトが有効か
	bool m_isActive;
	//座標
	DirectX::SimpleMath::Vector3 m_position;
	//大きさ
	DirectX::SimpleMath::Vector3 m_scale;

	// ポリゴン描画用
	// ポリゴン
	DirectX::VertexPositionTexture m_vertices[4];
	// ベーシックエフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	// インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_primitiveBatch;
	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// ビルボード行列
	DirectX::SimpleMath::Matrix m_billboardMat;

	// フレームカウンタ
	int m_frameCounter;
	// アニメーションキー
	int m_animationKey;



};
