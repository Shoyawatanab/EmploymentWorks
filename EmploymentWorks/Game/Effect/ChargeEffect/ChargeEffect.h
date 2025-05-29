/*
	チャージエフェクトクラス
*/
#pragma once
#include "Game/Interface/IEffect.h"

// 前方宣言
class ParticleUtility;


class ChargeEffect : public IEffect
{
public:
	//コンスタントバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
	};

	//インプットレイアウト
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	//生成間隔
	static constexpr float GENERATION_INTERVAL = 0.5f;
	//生成時間
	static constexpr float GENERATION_TIME = 1.5f;

public:
	//エフェクトが有効かどうか
	const bool& GetIsActive() override { return m_isActive; };
	//エフェクトが有効かどうかの登録
	void SetIsActive(const bool& isActive) override {	m_isActive = isActive;};
	//座標の登録
	void SetPosition(const DirectX::SimpleMath::Vector3& position) override { m_position = position; };
	//大きさの登録
	void SetScale(const DirectX::SimpleMath::Vector3& scale) override { m_scale = scale; };
	//エフェクトの種類のタグ
	EffectType GetEffectType()  override { return EffectType::CHARGE_EFFECT; };

public:
	//コンストラクタ
	ChargeEffect(CommonResources* resources);
	//デストラクタ
	~ChargeEffect() override;
	//初期化
	void Initialize() override;
	//更新処理
	void Update(const float& elapsedTime) override;
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const  DirectX::SimpleMath::Matrix& proj) override;

private:
	//エフェクトの生成
	void Create(void* datas) override;
	//シェーダーの作成
	void CreateShader();
	//ユーティリティの作成
	void CreateUtility();

private:
	// 共通リソース
	CommonResources* m_commonResources;
	//オブジェクトが有効かどうか
	bool m_isActive;
	//座標
	DirectX::SimpleMath::Vector3 m_position;
	//大きさ
	DirectX::SimpleMath::Vector3 m_scale;
	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	//	入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//	コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;
	//	テクスチャハンドル
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;
	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//	ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
	//ビルボード行列
	DirectX::SimpleMath::Matrix m_billboard;
	//頂点情報
	std::vector<DirectX::VertexPositionColorTexture> m_vertices;
	//ユーティリティクラス
	std::vector<ParticleUtility> m_ChargeEffectUtility;
	//時間
	float m_time;

};