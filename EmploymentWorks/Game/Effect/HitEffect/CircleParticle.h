/*
	ヒットエフェクトの円のパーティクル
*/
#pragma once
//前方宣言
class CommonResources;


class CircleParticle 
{
public:

	/// コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4    diffuse;
		DirectX::SimpleMath::Vector4    time;
		

	};

	//動作時間
	static constexpr float OPERATION_TIME = 2.0f;

public:
	//座標の登録
	void SetPosition(DirectX::SimpleMath::Vector3 pos) { m_position = pos; }
	//大きさの登録
	void SetScale(DirectX::SimpleMath::Vector3 scale) { m_scale = scale; }
	//時間の登録
	void SetTime(float time) { m_time = time; }


public:

	//コンストラクタ
	CircleParticle(CommonResources* resourece);
	//デストラクタ
	~CircleParticle();
	// 初期化
	void Initialize();
	// 更新処理
	bool Update(float elapsedTime);
	// 描画処理
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// 終了処理
	void Finalize();



private:

	//共通リソース
	CommonResources* m_commonResources;

	//座標
	DirectX::SimpleMath::Vector3 m_position;
	//大きさ
	DirectX::SimpleMath::Vector3 m_scale;
	//ワールド行列
	DirectX::SimpleMath::Matrix m_world;
	//透明度
	float m_alpha;

	//プリミティブ描画用のバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_Batch;
	//頂点レイアウトの定義
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	//テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//頂点レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;

	//経過時間
	float m_time;

};

