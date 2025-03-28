/*
	@file	ChargeEffect.h
	@brief	一般的なシーンクラス
*/
#pragma once
#include "Game/Interface/IEffect.h"

// 前方宣言
class ParticleUtility;


class ChargeEffect : public IEffect
{
public:
	//	データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
	};

	//	関数
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

public:

	ChargeEffect(CommonResources* resources);

	~ChargeEffect() override;

	void Initialize() override;
	void Update(const float& elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& view, const  DirectX::SimpleMath::Matrix& proj) override;


	bool GetIsActive() override { return m_isActive; };

	void SetIsActive(bool isActive) override;

	EffectType GetEffectType()  override { return EffectType::ChargeEffect; };


	void SetPosition(DirectX::SimpleMath::Vector3 position) override { m_position = position; };

	void SetScale(DirectX::SimpleMath::Vector3 scale) override { m_scale = scale; };

	void Create(void* datas) override;

	void LoadTexture(const wchar_t* path);



	void CreateShader();


	void CreateUtikity();

private:
	// 共通リソース
	CommonResources* m_commonResources;
	bool m_isActive;
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_scale;
	float m_timer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;


	//	入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//	コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;
	//	テクスチャハンドル
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;
	//	テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture2;
	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//	ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;
	DirectX::SimpleMath::Matrix m_billboard;
	std::vector<DirectX::VertexPositionColorTexture> m_vertices;


	DirectX::SimpleMath::Vector3 m_cameraPosition;
	DirectX::SimpleMath::Vector3 m_cameraTarget;


	std::vector<ParticleUtility> m_ChargeEffectUtility;

	float m_time;

};