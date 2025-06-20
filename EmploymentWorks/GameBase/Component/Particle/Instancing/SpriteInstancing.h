//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2025/06/16
// <file>			SpriteInstancing.h
// <概要>		　　スプライト版のインスタンシング
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"GameBase/Manager/ShaderManager2.h"

class SpriteInstancing
{
public:
	static const int MAX_INSTANCE = 100000;

	// 定数バッファ構造体
	struct SpriteConstantBuffer
	{
		DirectX::SimpleMath::Matrix view;
		DirectX::SimpleMath::Matrix projection;
		DirectX::SimpleMath::Vector4 CameraUp;
		DirectX::SimpleMath::Vector4 CameraRight;
		DirectX::SimpleMath::Vector4 color;
		bool onBillboard;
		DirectX::SimpleMath::Vector3 dammy;
		SpriteConstantBuffer()
		{
			memset(this, 0, sizeof(SpriteConstantBuffer));
		}
	};

	// インスタンス用データ構造体
	struct SpriteInstanceData
	{
		DirectX::SimpleMath::Vector3 position;
		DirectX::SimpleMath::Vector3 size;
		DirectX::SimpleMath::Vector4 color;
		DirectX::SimpleMath::Vector4 texCoord;
		DirectX::SimpleMath::Quaternion rotation;

		SpriteInstanceData()
		{
			position = DirectX::SimpleMath::Vector3::Zero;
			size = DirectX::SimpleMath::Vector3::One;
			color = DirectX::SimpleMath::Vector4::One;
			texCoord = DirectX::SimpleMath::Vector4(0.0f, 0.0f, 1.0f, 1.0f);
			rotation = DirectX::SimpleMath::Quaternion::Identity;
		}
	};

	// ベース頂点構造体
	struct BaseVertex
	{
		DirectX::SimpleMath::Vector3 position;
		DirectX::SimpleMath::Vector2 texCoord;
	};

public:
	// コンストラクタ、デストラクタ
	SpriteInstancing();
	~SpriteInstancing() = default;
	// 初期化
	void Initialize(ID3D11Device* device, int maxInstance = MAX_INSTANCE);
	// テクスチャ読み込み
	void SetTexture(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture) { m_texture = texture; }
	// ビルボード決定
	void SetBillboard(bool value) { m_onBillboard = value; }

	// 描画
	void Render(ID3D11DeviceContext* context,
		DirectX::DX11::CommonStates* states,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection,
		std::vector<SpriteInstanceData>& instances);
private:
	// 頂点バッファ作成
	void CreateVertexBuffer(ID3D11Device* device);
	// インスタンスバッファ作成
	void CreateInstanceBuffer(ID3D11Device* device);
	// カメラの右・上ベクトル計算
	void CalculateCameraVectors(const DirectX::SimpleMath::Matrix& view,
		DirectX::SimpleMath::Vector3& right, DirectX::SimpleMath::Vector3& up);
private:
	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	// インスタンスバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_instanceBuffer;
	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// シェーダセット
	ShaderSet m_shaderSet;
	// 定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	// インスタンス量
	int m_maxInstance;

	// ビルボードの有無 true == あり false == なし
	bool m_onBillboard;
};
