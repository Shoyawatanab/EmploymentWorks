//--------------------------------------------------------------------------------------
// File: Particle.h
//
// シーンの雛型に使用してください
//
// Date: 2023.3.25
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once
class CommonResources;



class Particle 
{
public:

	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4    diffuse;
		DirectX::SimpleMath::Vector4    time;

	};

	enum State
	{
		None,
		Using

	};

private:

	CommonResources* m_commonResources;


	Microsoft::WRL::ComPtr<ID3D11Resource> m_res;


	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_Texture;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_Batch;



	DirectX::SimpleMath::Matrix m_billBoard;
	float m_angleX;
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_scale;
	float m_alpha;

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	int m_textureWidth, m_textureHeight;

	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;

	DirectX::SimpleMath::Matrix m_world;

	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	
	float m_time;

	State m_state;

public:

	// コンストラクタ
	Particle();
	~Particle();

	// 初期化
	void Initialize(CommonResources* resourece);

	// 更新
	void Update(float elapsedTime) ;

	// 描画
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj) ;

	// 終了処理
	void Finalize() ;

	void SetState(State state) { m_state = state; }
	State& GetState() { return m_state; }

	void Create(DirectX::SimpleMath::Vector3 Pos);
};

