/*
	@file	ChargeEffect.cpp
	@brief	一般的なシーンクラス
*/
#include "pch.h"
#include "ChargeEffect.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Libraries/MyLib/BinaryFile.h"
#include "Game/Observer/EventParams.h"
#include "Game/Effect/Particle/ParticleUtility.h"
#include "Libraries/WataLib/GameResources.h"

#include <algorithm>
#include <random>
#include <cmath>

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// インプットレイアウト
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> ChargeEffect::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0,							 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	0, sizeof(SimpleMath::Vector3) + sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
ChargeEffect::ChargeEffect(CommonResources* resources)
	:
	m_commonResources{ resources },
	m_timer{}
	, m_isActive{ false }
	, m_CBuffer{}
	, m_inputLayout{}
	, m_batch{}
	, m_states{}
	, m_texture{}
	, m_vertexShader{}
	, m_pixelShader{}
	, m_geometryShader{}
	, m_world{}
	, m_view{}
	, m_proj{}
	, m_billboard{}
	, m_vertices{}
	, m_cameraPosition{}
	, m_cameraTarget{}
	, m_ChargeEffectUtility{}
	, m_position{}
	, m_scale{}
	,m_time{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
ChargeEffect::~ChargeEffect()
{
}

/// <summary>
/// 初期化
/// </summary>
void ChargeEffect::Initialize()
{

	ID3D11Device1* device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	ID3D11DeviceContext1* context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	//	シェーダーの作成
	CreateShader();

	//	画像の読み込み（２枚ともデフォルトは読み込み失敗でnullptr)
	//LoadTexture(L"Resources/Textures/da.png");

	m_texture.push_back(m_commonResources->GetGameResources()->GetTexture("da"));

	//	プリミティブバッチの作成
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);

	m_states = std::make_unique<CommonStates>(device);



}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
void ChargeEffect::Update(const float& elapsedTime)
{
	if (!m_isActive)
	{
		return;
	}

	for (auto it = m_ChargeEffectUtility.begin(); it != m_ChargeEffectUtility.end(); )
	{
		if (!it->Update(elapsedTime)) {
			it = m_ChargeEffectUtility.erase(it);  // 削除後の新しいイテレーターを取得
		}
		else {
			++it;  // 削除しなかった場合は次の要素へ
		}
	}


	if (fmod(m_time, 0.5f) < elapsedTime)
	{
		CreateUtikity();

	}


	if (m_time >= 1.5f)
	{
		m_time = 0.0f;
		m_isActive = false;
	}

	m_time += elapsedTime;


}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void ChargeEffect::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	if (!m_isActive)
	{
		return;
	}

	ID3D11DeviceContext1* context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	//	頂点情報(板ポリゴンの４頂点の座標情報）


	//	登録されている頂点をリセット
	m_vertices.clear();
	for (ParticleUtility& li : m_ChargeEffectUtility)
	{
		VertexPositionColorTexture vPCT;
		//	表示するパーティクルの中心座標のみを入れる。
		//	→つまり、C++で用意しているデータだけではテクスチャを表示できない。
		//	　→ジオメトリシェーダを使う事前提のデータ、ということ
		vPCT.position = XMFLOAT3(li.GetPosition());
		//	テクスチャの色
		vPCT.color = XMFLOAT4(li.GetNowColor());
		//	現在のテクスチャのスケールを「XMFLOAT2」のXに入れる。
		//	Yは使っていないし、そもそものTextureのUV座標とは違う使い方になっていることに注意
		vPCT.textureCoordinate = XMFLOAT2(li.GetNowScale().x, 0.0f);

		m_vertices.push_back(vPCT);
	}

	//	表示する点がない場合は描画を終わる
	if (m_vertices.empty())
	{
		m_isActive = false;
		return;
	}


	// ビルボードマトリックスを計算する
	m_billboard = view.Invert();
	m_billboard._41 = 0.0f;
	m_billboard._42 = 0.0f;
	m_billboard._43 = 0.0f;

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.matWorld = m_billboard.Transpose();
	cbuff.Diffuse = SimpleMath::Vector4(1, 1, 1, 1);

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//	画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//	半透明描画指定		補間アルファ合成
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	//	透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	深度バッファに書き込み参照する
	context->OMSetDepthStencilState(m_states->DepthRead(), 0);

	//	カリングはなし
	context->RSSetState(m_states->CullNone());

	//	シェーダをセットする
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//	ピクセルシェーダにテクスチャを登録する。
	for (int i = 0; i < m_texture.size(); i++)
	{
		context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}

	//	インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	//	指定した座標を中心に、シェーダ側で板ポリゴンを生成・描画させる
	m_batch->Begin();

	//	ここまでの処理の関係上、以下は使えない
	//m_batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);

	//	ジオメトリシェーダでPointを受け取ることになっているため、
	//	ここではD3D11_PRIMITIVE_TOPOLOGY_POINTLISTを使う
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices[0], m_vertices.size());

	m_batch->End();

	//	シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);


}

void ChargeEffect::SetIsActive(bool isActive)
{
	m_isActive = isActive;

}

void ChargeEffect::Create(void* datas)
{

	CreateChargeEffectDatas* data = static_cast<CreateChargeEffectDatas*>(datas);

	m_position = data->Position;

	CreateUtikity();

	m_time = 0.0f;

}

/// <summary>
/// テクスチャリソース読み込み関数
/// </summary>
/// <param name="path">相対パス(Resources/Textures/・・・.pngなど）</param>
void ChargeEffect::LoadTexture(const wchar_t* path)
{

	ID3D11Device1* device = m_commonResources->GetDeviceResources()->GetD3DDevice();


	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	DirectX::CreateWICTextureFromFile(device, path, nullptr, texture.ReleaseAndGetAddressOf());

	m_texture.push_back(texture);
}



/// <summary>
/// Shader作成部分だけ分離した関数
/// </summary>
void ChargeEffect::CreateShader()
{
	ID3D11Device1* device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	//	コンパイルされたシェーダファイルを読み込み
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticlePS.cso");

	//	インプットレイアウトの作成
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	//	頂点シェーダ作成
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{//	エラー
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	//	ジオメトリシェーダ作成
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_geometryShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	//	ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);



}

void ChargeEffect::CreateUtikity()
{

	int count = 12;
	float radius = 2.0f;
	Vector3 scale = Vector3(2, 2, 2);


	for (int i = 0; i < count; i++)
	{
		//角度を求める
		float angle = DirectX::XM_2PI * i / count;
		float x = radius * cos(angle);
		float z = radius * sin(angle);

		Vector3 pos = Vector3(x, 0.0f, z);

		Vector3 velocity = Vector3(cos(angle), 0.0f, sin(angle));

		//	0～2PIの値をdefault_random_engine(恐らくしばらくはmt19937)を使って取り出す
		ParticleUtility pU(
			3.0f,																			//	生存時間(s)
			pos + m_position,				                                                        //	基準座標
			velocity,		//	速度
			SimpleMath::Vector3(0.5f,0.0f,0.5f),														//	加速度
			scale,                                                      //	初期スケール
			scale,							                  //	最終スケール
			SimpleMath::Color(1.f, 1.f, 1.f, 1.f),											// 初期カラー、
			SimpleMath::Color(1.f, 1.f, 1.f, -1.f)										   //	最終カラー
		);

		m_ChargeEffectUtility.push_back(pU);
	}




}


