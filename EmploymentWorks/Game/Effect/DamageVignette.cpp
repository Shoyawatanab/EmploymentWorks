/*
	@file	DamageVignette.cpp
	@brief	一般的なシーンクラス
*/
#include "pch.h"
#include "DamageVignette.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Libraries/MyLib/BinaryFile.h"




///	<summary>
///	インプットレイアウト
///	</summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> DamageVignette::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
DamageVignette::DamageVignette(CommonResources* resources)
	:
	m_commonResources{resources},
	m_position{},
	m_scale{}
	,m_isActive{false}
	,m_alpha{}
	,m_damageCount{}
	,m_CBuffer{}
	,m_inputLayout{}
	,m_batch{}
	,m_vs{}
	,m_ps{}
	,m_gs{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
DamageVignette::~DamageVignette()
{
	Finalize();
}


/// <summary>
/// 初期化
/// </summary>
void DamageVignette::Initialize()
{
	//デバイスの取得
	auto device  = m_commonResources->GetDeviceResources()->GetD3DDevice();
	//コンテキストの取得
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	//	コンパイルされたシェーダファイルを読み込み
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/DamageVignetteVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/DamageVignetteGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/DamageVignettePS.cso");



	//	インプットレイアウトの作成
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	//	頂点シェーダ作成
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vs.ReleaseAndGetAddressOf())))
	{//	エラー
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	//	ジオメトリシェーダ作成
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_gs.ReleaseAndGetAddressOf())))
	{//	エラー
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}

	//	ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_ps.ReleaseAndGetAddressOf())))
	{//	エラー
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

	//	プリミティブバッチの作成
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(context);




}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void DamageVignette::Update(const float& elapsedTime)
{
	//オブジェクトが有効か
	if (!m_isActive)
	{
		return;
	}

	//透明度の更新
	m_alpha -= elapsedTime * 1.0f;

	//透明になったら
	if (m_alpha <= 0)
	{
		m_isActive = false;
	}

}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void DamageVignette::Render(const DirectX::SimpleMath::Matrix& view, const  DirectX::SimpleMath::Matrix& proj)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(proj);

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	if (!m_isActive)
	{
		return;
	}
	//コンテキストの取得
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	//デバイスの取得
	auto states = m_commonResources->GetCommonStates();


	//	頂点情報(板ポリゴンの４頂点の座標情報）
	VertexPositionColorTexture vertex[4] =
	{
		VertexPositionColorTexture(Vector3(0.0f,  0.0f, 0.0f),Vector4::One,Vector2(0.0f, 0.0f)),
	};

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	cbuff.matView =  Matrix::Identity;
	cbuff.matProj =  Matrix::Identity;
	cbuff.matWorld = Matrix::Identity;
	cbuff.Diffuse =  Vector4(1, 1, 1, 1);
	cbuff.Time =     Vector4(m_alpha, 0.0f, 0.0f, 0.0f);

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//	画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//	半透明描画指定
	ID3D11BlendState* blendstate = states->NonPremultiplied();

	//	透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	深度バッファに書き込み参照する
	context->OMSetDepthStencilState(states->DepthDefault(), 0);

	//	カリングは左周り
	context->RSSetState(states->CullNone());

	//	シェーダをセットする
	context->VSSetShader(m_vs.Get(), nullptr, 0);
	context->GSSetShader(m_gs.Get(), nullptr, 0);
	context->PSSetShader(m_ps.Get(), nullptr, 0);



	//	インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	//	板ポリゴンを描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	m_batch->End();

	//	シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);






}

void DamageVignette::SetIsActive(bool isActive)
{
	 m_isActive = isActive; 
	 //透明度の初期化
	 m_alpha = 1;
}

/// <summary>
/// エフェクトの作成
/// </summary>
/// <param name="datas">データ</param>
void DamageVignette::Create(void* datas)
{
	UNREFERENCED_PARAMETER(datas);

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void DamageVignette::Finalize()
{
	// do nothing.
}


