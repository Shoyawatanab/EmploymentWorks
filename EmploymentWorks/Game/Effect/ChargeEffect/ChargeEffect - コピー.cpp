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


using namespace DirectX;
using namespace DirectX::SimpleMath;

///	<summary>
///	インプットレイアウト
///	</summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> ChargeEffect::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
ChargeEffect::ChargeEffect(CommonResources* resources)
	:
	m_commonResources{resources},
	m_position{},
	m_scale{}
	,m_isActive{false}
	, m_time{}
	,m_damageCount{}
	,m_CBuffer{}
	,m_inputLayout{}
	,m_batch{}
	,m_vs{}
	,m_ps{}
	,m_gs{}
	,m_world{}
	,m_view{}
	,m_proj{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
ChargeEffect::~ChargeEffect()
{
	Finalize();
}


/// <summary>
/// 初期化
/// </summary>
void ChargeEffect::Initialize()
{

	auto device  = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states  = m_commonResources->GetCommonStates();



	//	コンパイルされたシェーダファイルを読み込み
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ChargeEffectVS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ChargeEffectPS.cso");



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
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>(context);




}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void ChargeEffect::Update(const float& elapsedTime)
{
	if (!m_isActive)
	{
		return;
	}


		//経過時間の加算
	m_time += elapsedTime;

	//終了したら
	if (m_time >= 2)
	{
		//m_isActive = false;
	}



}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void ChargeEffect::Render(const DirectX::SimpleMath::Matrix& view, const  DirectX::SimpleMath::Matrix& proj)
{

	if (!m_isActive)
	{
		return;
	}

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();


	//頂点データ
	//VertexPositionTexture vertex[4] = {
	//	VertexPositionTexture(SimpleMath::Vector3(-0.5f,-0.5f ,0.0f), SimpleMath::Vector2(0.0f, 0.0f)),
	//	VertexPositionTexture(SimpleMath::Vector3(0.5f ,-0.5f ,0.0f), SimpleMath::Vector2(1.0f, 0.0f)),
	//	VertexPositionTexture(SimpleMath::Vector3(0.5f,0.5f  ,0.0f), SimpleMath::Vector2(1.0f, 1.0f)),
	//	VertexPositionTexture(SimpleMath::Vector3(-0.5f,0.5f ,0.0f), SimpleMath::Vector2(0.0f, 1.0f)),
	//};

	VertexPositionTexture vertex[4] = {
	VertexPositionTexture(SimpleMath::Vector3(-0.5f,-0.0f ,-0.5f), SimpleMath::Vector2(0.0f, 0.0f)),
	VertexPositionTexture(SimpleMath::Vector3(0.5f ,-0.0f ,-0.5f), SimpleMath::Vector2(1.0f, 0.0f)),
	VertexPositionTexture(SimpleMath::Vector3(0.5f,0.0f  ,0.5f), SimpleMath::Vector2(1.0f, 1.0f)),
	VertexPositionTexture(SimpleMath::Vector3(-0.5f,0.0f ,0.5f), SimpleMath::Vector2(0.0f, 1.0f)),
	};


	Vector3 pos = m_position;
	pos.y = 1.0f;

	Matrix matrix = Matrix::CreateScale(m_scale);
	matrix *= Matrix::CreateTranslation(pos);




	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.matWorld = matrix.Transpose();
	cbuff.Diffuse = SimpleMath::Vector4(1, 1, 1, 1);
	cbuff.Time = SimpleMath::Vector4(m_time, 0.0f, 0.0f, 0.0f);

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
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
	context->PSSetShader(m_ps.Get(), nullptr, 0);



	//	インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	//	板ポリゴンを描画
	m_batch->Begin();
	m_batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	m_batch->End();

	//	シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);






}

void ChargeEffect::SetIsActive(bool isActive)
{
	 m_isActive = isActive; 

	 m_time = 0;
}

void ChargeEffect::Create(void* datas)
{

	EventParams::CreateChargeEffectDatas* data = static_cast<EventParams::CreateChargeEffectDatas*>(datas);

	DirectX::SimpleMath::Vector3 pos = data->Position;
	DirectX::SimpleMath::Vector3 scale = data->Scale;

	m_position = pos;

	m_scale = scale;

	m_position = Vector3::Zero;


}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void ChargeEffect::Finalize()
{
	// do nothing.
}


