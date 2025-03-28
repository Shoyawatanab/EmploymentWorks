/*
	@file	ChargeEffect.h
	@brief	一般的なシーンクラス
*/
#pragma once
#include "Game/Interface/IEffect.h"

// 前方宣言

class ChargeEffect : public IEffect
{
public:

	static constexpr DirectX::SimpleMath::Vector2 SCALE {2, 2};

	//	関数
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


	//	データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
		DirectX::SimpleMath::Vector4	Time;
	};

public:

	bool GetIsActive() override { return m_isActive; };

	void SetIsActive(bool isActive) override;

	EffectType GetEffectType()  override { return EffectType::ChargeEffect; };


	void SetPosition(DirectX::SimpleMath::Vector3 position) override { m_position = position; };

	void SetScale(DirectX::SimpleMath::Vector3 scale) override { m_scale = scale; };



public:
	ChargeEffect(CommonResources* resources);

	~ChargeEffect() override;

	void Initialize() override;
	void Update(const float& elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& view, const  DirectX::SimpleMath::Matrix& proj) override;

	void Finalize();


	void Create(void* datas) override;

private:

	// 共通リソース
	CommonResources* m_commonResources;
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_scale;
	bool m_isActive;
	float m_time;
	int m_damageCount;

	//コンストバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	//	入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_batch;
	//	使用する頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vs;
	//	使用するピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_ps;
	//	使用するジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_gs;
	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;



};
