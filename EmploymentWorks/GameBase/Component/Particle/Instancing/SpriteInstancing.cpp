//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2025/06/16
// <file>			SpriteInstancing.cpp
// <概要>		　　スプライト版のインスタンシング
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"SpriteInstancing.h"

/// <summary>
/// スプライトインスタンシング用入力レイアウト
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> SPRITE_INSTANCE_INPUT_LAYOUT =
{
	// ベース頂点（ポイント）
	{ "POSITION",			0, DXGI_FORMAT_R32G32B32_FLOAT		, 0, 0	, D3D11_INPUT_PER_VERTEX_DATA	, 0 },
	{ "TEXCOORD",			0, DXGI_FORMAT_R32G32_FLOAT			, 0, 12	, D3D11_INPUT_PER_VERTEX_DATA	, 0 },
	// インスタンスデータ
	{ "INSTANCEPOS",		0, DXGI_FORMAT_R32G32B32_FLOAT		, 1, 0	, D3D11_INPUT_PER_INSTANCE_DATA	, 1 },
	{ "INSTANCESIZE",		0, DXGI_FORMAT_R32G32B32_FLOAT		, 1, 12	, D3D11_INPUT_PER_INSTANCE_DATA	, 1 },
	{ "INSTANCECOLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT	, 1, 24	, D3D11_INPUT_PER_INSTANCE_DATA	, 1 },
	{ "INSTANCETEXCOORD",	0, DXGI_FORMAT_R32G32B32A32_FLOAT	, 1, 40	, D3D11_INPUT_PER_INSTANCE_DATA	, 1 },
	{ "INSTANCEROT" ,		0, DXGI_FORMAT_R32G32B32A32_FLOAT	, 1, 56 , D3D11_INPUT_PER_INSTANCE_DATA , 1	}
};

/// <summary>
/// コンストラクタ
/// </summary>
SpriteInstancing::SpriteInstancing()
{
	m_maxInstance = 0;
	m_onBillboard = true;
}

/// <summary>
/// 初期化処理
/// </summary>
void SpriteInstancing::Initialize(ID3D11Device* device, int maxInstance)
{
	// インスタンスの量決定
	m_maxInstance = std::min(maxInstance, MAX_INSTANCE);
	// シェーダの作成
	m_shaderSet.vertexShader = ShaderManager2::CreateVSShader(device, "SpriteVS.cso");
	m_shaderSet.pixelShader = ShaderManager2::CreatePSShader(device, "SpritePS.cso");
	m_shaderSet.inputLayout = ShaderManager2::CreateInputLayout(device, SPRITE_INSTANCE_INPUT_LAYOUT, "SpriteVS.cso");
	// 定数バッファ作成
	m_constantBuffer = ShaderManager2::CreateConstantBuffer<SpriteConstantBuffer>(device);



	// バッファ作成
	CreateVertexBuffer(device);
	CreateInstanceBuffer(device);
}

/// <summary>
/// 描画処理
/// </summary>
void SpriteInstancing::Render(ID3D11DeviceContext* context,
	DirectX::DX11::CommonStates* states,
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection,
	std::vector<SpriteInstanceData>& instances)
{
	if (instances.empty()) { return; }
	if (instances.size() > static_cast<size_t>(m_maxInstance)) { return; }

	// 実際に描画するインスタンス数
	int instanceCount = static_cast<int>(std::min(instances.size(), static_cast<size_t>(m_maxInstance)));
	// インスタンスバッファ更新
	D3D11_MAPPED_SUBRESOURCE mappedResources;
	if (SUCCEEDED(context->Map(m_instanceBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResources)))
	{
		memcpy(mappedResources.pData, instances.data(), sizeof(SpriteInstanceData) * instanceCount);
		context->Unmap(m_instanceBuffer.Get(), 0);
	}
	// カメラの右、上ベクトル計算
	DirectX::SimpleMath::Vector3 cameraRight, cameraUp;
	CalculateCameraVectors(view, cameraRight, cameraUp);

	// 定数バッファ更新
	SpriteConstantBuffer cb;
	cb.view = view.Transpose();
	cb.projection = projection.Transpose();
	cb.CameraRight = DirectX::SimpleMath::Vector4(cameraRight.x, cameraRight.y, cameraRight.z, 0.0f);
	cb.CameraUp = DirectX::SimpleMath::Vector4(cameraUp.x, cameraUp.y, cameraUp.z, 0.0f);
	cb.color = DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	cb.onBillboard = m_onBillboard;

	context->UpdateSubresource(m_constantBuffer.Get(), 0, nullptr, &cb, 0, 0);

	// レンダリングステート設定
	ID3D11Buffer* pBuffers[2] = { m_vertexBuffer.Get(), m_instanceBuffer.Get() };
	UINT strides[2] = { sizeof(BaseVertex), sizeof(SpriteInstanceData) };
	UINT offsets[2] = { 0, 0 };
	context->IASetVertexBuffers(0, 2, pBuffers, strides, offsets);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetInputLayout(m_shaderSet.inputLayout.Get());

	// シェーダー設定
	context->VSSetShader(m_shaderSet.vertexShader.Get(), nullptr, 0);
	context->PSSetShader(m_shaderSet.pixelShader.Get(), nullptr, 0);

	// 定数バッファ設定
	ID3D11Buffer* pConstantBuffer = m_constantBuffer.Get();
	context->VSSetConstantBuffers(0, 1, &pConstantBuffer);
	context->GSSetConstantBuffers(0, 1, &pConstantBuffer);
	context->PSSetConstantBuffers(0, 1, &pConstantBuffer);

	// テクスチャとサンプラー設定
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());
	ID3D11SamplerState* pSampler = states->LinearWrap();
	context->PSSetSamplers(0, 1, &pSampler);

	// ブレンドステート（アルファブレンド）
	context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xffffffff);
	// デプスステンシルステート
	context->OMSetDepthStencilState(states->DepthDefault(), 0);
	// ラスタライザーステート
	context->RSSetState(states->CullNone());

	// 描画（6個の頂点で四角形を作成）
	context->DrawInstanced(6, instanceCount, 0, 0);
}

/// <summary>
/// 頂点シェーダ作成
/// </summary>
/// <param name="device"></param>
void SpriteInstancing::CreateVertexBuffer(ID3D11Device* device)
{
	using namespace DirectX::SimpleMath;

	// 四角形の頂点データ（6個の頂点で三角形を2個）
	BaseVertex vertices[6] = {
		// 三角形1（左下、右下、左上）
		{ Vector3(-0.5f, -0.5f, 0.0f), Vector2(0.0f, 1.0f) },
		{ Vector3(0.5f, -0.5f, 0.0f), Vector2(1.0f, 1.0f) },
		{ Vector3(-0.5f, 0.5f, 0.0f), Vector2(0.0f, 0.0f) },
		// 三角形2（左上、右下、右上）
		{ Vector3(-0.5f, 0.5f, 0.0f), Vector2(0.0f, 0.0f) },
		{ Vector3(0.5f, -0.5f, 0.0f), Vector2(1.0f, 1.0f) },
		{ Vector3(0.5f, 0.5f, 0.0f), Vector2(1.0f, 0.0f) }
	};

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	bufferDesc.ByteWidth = sizeof(vertices);
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices;

	device->CreateBuffer(&bufferDesc, &initData, &m_vertexBuffer);
}

/// <summary>
/// 定数バッファの作成
/// </summary>
void SpriteInstancing::CreateInstanceBuffer(ID3D11Device* device)
{
	// 動的インスタンスバッファ作成
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = sizeof(SpriteInstanceData) * m_maxInstance;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	device->CreateBuffer(&bufferDesc, nullptr, &m_instanceBuffer);
}

/// <summary>
/// カメラベクトルの計算
/// </summary>
void SpriteInstancing::CalculateCameraVectors(const DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Vector3& right, DirectX::SimpleMath::Vector3& up)
{
	// ビュー行列から、カメラの右、上ベクトルを抽出
	right = DirectX::SimpleMath::Vector3(view._11, view._21, view._31);
	up = DirectX::SimpleMath::Vector3(view._12, view._22, view._32);

	right.Normalize();
	up.Normalize();
}