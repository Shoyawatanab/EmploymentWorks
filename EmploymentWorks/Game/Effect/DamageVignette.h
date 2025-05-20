/*
	@file	DamageVignette.h
	@brief	一般的なシーンクラス
*/
#pragma once
#include "Game/Interface/IEffect.h"



class DamageVignette : public IEffect
{
public:

	static constexpr DirectX::SimpleMath::Vector2 SCALE {2, 2};

	//	関数
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


	//コンスタントバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
		DirectX::SimpleMath::Vector4	Time;
	};

public:
	//オブジェクトが有効か
	bool GetIsActive() override { return m_isActive; };
	//オブジェクトが有効かの登録
	void SetIsActive(bool isActive) override;
	//座標の登録
	void SetPosition(DirectX::SimpleMath::Vector3 position) override { m_position = position; };
	//大きさの登録
	void SetScale(DirectX::SimpleMath::Vector3 scale) override { m_scale = scale; };
	//エフェクトの種類のタグ
	EffectType GetEffectType()  override { return EffectType::PLAYER_DAMAGE; };


public:
	//コンストラクタ
	DamageVignette(CommonResources* resources);
	//デストラクタ
	~DamageVignette() override;
	//初期化
	void Initialize() override;
	//更新処理
	void Update(const float& elapsedTime) override;
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const  DirectX::SimpleMath::Matrix& proj) override;
	//
	void Finalize();

private:
	//エフェクトの作成
	void Create(void* datas) override;

private:

	// 共通リソース
	CommonResources* m_commonResources;
	//座標
	DirectX::SimpleMath::Vector3 m_position;
	//大きさ
	DirectX::SimpleMath::Vector3 m_scale;
	//オブジェクトが有効か
	bool m_isActive;
	//透明度
	float m_alpha;
	//ダメージ
	int m_damageCount;

	//コンストバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	//	入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//	使用する頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vs;
	//	使用するピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_ps;
	//	使用するジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_gs;




};
