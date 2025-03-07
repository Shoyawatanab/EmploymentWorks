//--------------------------------------------------------------------------------------
//	File: Fade.h
//
//	パーティクルクラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Fade.h"
#include "BinaryFile.h"
#include "DeviceResources.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>

const float FADESPEED = 100.0f;

const float MAXFADETIME = 2.0f;

///	<summary>
///	インプットレイアウト
///	</summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> Fade::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3)+ sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

///	<summary>
///	コンストラクタ
///	</summary>
Fade::Fade(ID3D11Device1* device, ID3D11DeviceContext* contect)
	:
	m_time{}
	,m_fadeState{}
	,m_isSceneChange{}
	,m_device{device}
	, m_context{contect}
{
	//初期化
	Initialize();
}

///	<summary>
///	デストラクタ
///	</summary>
Fade::~Fade()
{
}

void Fade::Initialize()
{

	//	シェーダーの作成
	CreateShader();

	//	プリミティブバッチの作成
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(m_context);

	m_states = std::make_unique<DirectX::CommonStates>(m_device);

	m_currentPS = m_normalFadeInPS.Get();

	m_fadeState = FadeState::None;
	m_time = 0;

	m_maxFadeTime = MAXFADETIME;

	m_isSceneChange = false;


}

void Fade::Update(float elapsdTime)
{
	//フェード中じゃなければ
	if (m_fadeState == FadeState::None)
	{
		return;
	}

	if (m_time >= MAXFADETIME)
	{

		switch (m_fadeState)
		{
			case Fade::None:
				break;
			case Fade::FadeIn:
				m_isSceneChange = true;

				break;
			case Fade::FadeOut:
				m_isSceneChange = false;

				break;
			default:
				break;
		}


		m_fadeState = FadeState::None;

		return;
	}


 	m_time += elapsdTime ;
	

}

//通常フェードの開始関数
void Fade::StartNormalFadeIn()
{

	m_fadeState = FadeState::FadeIn;

	m_time = 0;

	m_currentPS = m_normalFadeInPS.Get();

}



void Fade::StartNormalFadeOut()
{
	m_fadeState = FadeState::FadeOut;
	m_time = 0;

	m_currentPS = m_normalFadeOutPS.Get();
}

///	<summary>
///	Shader作成部分だけ分離した関数
///	</summary>
void Fade::CreateShader()
{

	//	コンパイルされたシェーダファイルを読み込み
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/FadeVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/FadeGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/NormalFadeInPS.cso");

	BinaryFile PSData2 = BinaryFile::LoadFile(L"Resources/Shaders/NormalFadeOutPS.cso");


	//	インプットレイアウトの作成
	m_device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	//	頂点シェーダ作成
	if (FAILED(m_device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_currentVS.ReleaseAndGetAddressOf())))
	{//	エラー
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	//	ジオメトリシェーダ作成
	if (FAILED(m_device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_currentGS.ReleaseAndGetAddressOf())))
	{//	エラー
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}

	//	ピクセルシェーダ作成
	if (FAILED(m_device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_normalFadeInPS.ReleaseAndGetAddressOf())))
	{//	エラー
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	//	ピクセルシェーダ作成
	if (FAILED(m_device->CreatePixelShader(PSData2.GetData(), PSData2.GetSize(), NULL, m_normalFadeOutPS.ReleaseAndGetAddressOf())))
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
	m_device->CreateBuffer(&bd, nullptr, &m_CBuffer);


}

///	<summary>
///	描画関数
///	</summary>
///	<param name="view">ビュー行列</param>
///	<param name="proj">射影行列</param>
void Fade::Render()
{

	//	頂点情報(板ポリゴンの４頂点の座標情報）
	DirectX::VertexPositionColorTexture vertex[4] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(0.0f,  0.0f, 0.0f), DirectX::SimpleMath::Vector4::One, DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
	};

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	cbuff.matView = DirectX::SimpleMath::Matrix::Identity;
	cbuff.matProj = DirectX::SimpleMath::Matrix::Identity;
	cbuff.matWorld = DirectX::SimpleMath::Matrix::Identity;
	cbuff.Diffuse = DirectX::SimpleMath::Vector4(1, 1, 1, 1);
	cbuff.time = DirectX::SimpleMath::Vector4(m_time, m_maxFadeTime, 1, 1);

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	m_context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	m_context->VSSetConstantBuffers(0, 1, cb);
	m_context->GSSetConstantBuffers(0, 1, cb);
	m_context->PSSetConstantBuffers(0, 1, cb);

	//	画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	m_context->PSSetSamplers(0, 1, sampler);


	//	半透明描画指定
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	//	透明判定処理
	m_context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	深度バッファに書き込み参照する
	m_context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	//	カリングは左周り
	m_context->RSSetState(m_states->CullNone());

	//	シェーダをセットする
	m_context->VSSetShader(m_currentVS.Get(), nullptr, 0);
	m_context->GSSetShader(m_currentGS.Get(), nullptr, 0);
	m_context->PSSetShader(m_currentPS.Get(), nullptr, 0);

	//	ピクセルシェーダにテクスチャを登録する。
	for (int i = 0; i < m_texture.size(); i++)
	{
		m_context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}

	//	インプットレイアウトの登録
	m_context->IASetInputLayout(m_inputLayout.Get());

	//	板ポリゴンを描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 4);
	m_batch->End();

	//	シェーダの登録を解除しておく
	m_context->VSSetShader(nullptr, nullptr, 0);
	m_context->GSSetShader(nullptr, nullptr, 0);
	m_context->PSSetShader(nullptr, nullptr, 0);

}


