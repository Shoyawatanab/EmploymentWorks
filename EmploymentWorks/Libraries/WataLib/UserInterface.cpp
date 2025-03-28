//--------------------------------------------------------------------------------------
// File: UserInterface.h
//
// ユーザーインターフェースクラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "UserInterface.h"

#include "BinaryFile.h"
#include "DeviceResources.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>
#include "Game/Screen.h"

using namespace DirectX;

/// <summary>
/// インプットレイアウト
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> UserInterface::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(SimpleMath::Vector3) + sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// コンストラクタ
/// </summary>
UserInterface::UserInterface()
	:m_pDR(nullptr)
	, m_textureHeight(0)
	, m_textureWidth(0)
	, m_texture(nullptr)
	, m_res(nullptr)
	, m_scale(SimpleMath::Vector2::One)
	, m_position(SimpleMath::Vector2::Zero)
	, m_renderRatio(1.0f)
	, m_renderRatioOffset(0.0f)
	, m_alphaValue{ 1.0f }
	,m_isActive{true}
{

}

/// <summary>
/// デストラクタ
/// </summary>
UserInterface::~UserInterface()
{
}

/// <summary>
/// テクスチャリソース読み込み関数
/// </summary>
/// <param name="path">相対パス(Resources/Textures/・・・.pngなど）</param>
void UserInterface::LoadTexture(const wchar_t* path)
{
	//	善子画像を読み込む
	/*HRESULT result; = DirectX::CreateWICTextureFromFile(m_pDR->GetD3DDevice(), L"Resources/Textures/yoshiko.jpg", m_yoshiRes.ReleaseAndGetAddressOf(), m_yoshiTexture.ReleaseAndGetAddressOf());
	Microsoft::WRL::ComPtr<ID3D11Texture2D> yoshiTex;
	DX::ThrowIfFailed(m_yoshiRes.As(&yoshiTex));*/

	//	指定された画像を読み込む
	DirectX::CreateWICTextureFromFile(m_pDR->GetD3DDevice(), path, m_res.ReleaseAndGetAddressOf(), m_texture.ReleaseAndGetAddressOf());
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;
	DX::ThrowIfFailed(m_res.As(&tex));

	//	読み込んだ画像の情報を取得する
	D3D11_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);

	//	読み込んだ画像のサイズを取得する
	m_textureWidth = desc.Width;
	m_textureHeight = desc.Height;



}

/// <summary>
/// 生成関数
/// </summary>
/// <param name="pDR">ユーザーリソース等から持ってくる</param>
void UserInterface::Create(DX::DeviceResources* pDR
	, const wchar_t* path
	, DirectX::SimpleMath::Vector2 position
	, DirectX::SimpleMath::Vector2 scale
	)
{
	m_pDR = pDR;
	auto device = pDR->GetD3DDevice();
	m_position = position;
	m_initialPosition = position;
	m_scale = scale;
	m_initialScale = scale;

	//シェーダーの作成
	CreateUIShader();

	//	画像の読み込み
	LoadTexture(path);

	//	プリミティブバッチの作成
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(pDR->GetD3DDeviceContext());

	m_states = std::make_unique<CommonStates>(device);


}

void UserInterface::SetScale(DirectX::SimpleMath::Vector2 scale)
{
	m_scale = scale;
}
void UserInterface::SetPosition(DirectX::SimpleMath::Vector2 position)
{
	m_position = position;
}



void UserInterface::SetRenderRatio(float ratio)
{
	m_renderRatio = ratio;
}




void UserInterface::CreateUIShader()
{
	auto device = m_pDR->GetD3DDevice();

	//	コンパイルされたシェーダファイルを読み込み
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/UIVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/UIGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/UIPS.cso");

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



/// <summary>
/// 描画関数
/// </summary>
void UserInterface::Render()
{

	if (!m_isActive)
	{
		return;
	}

	auto context = m_pDR->GetD3DDeviceContext();
	// 頂点情報
	// Position.xy	:拡縮用スケール
	// Position.z	:アンカータイプ(0〜8)の整数で指定
	// Color.xy　	:アンカー座標(ピクセル指定:1280 ×720)
	// Color.zw		:画像サイズ
	// Tex.xy		:ウィンドウサイズ（バッファも同じ。こちらは未使用）
	VertexPositionColorTexture vertex[1] = {
		VertexPositionColorTexture(
			 SimpleMath::Vector3(m_scale.x, m_scale.y, ANCHOR::MIDDLE_CENTER)
			,SimpleMath::Vector4(m_position.x, m_position.y, static_cast<float>(m_textureWidth), static_cast<float>(m_textureHeight))
			,SimpleMath::Vector2(m_renderRatio - m_renderRatioOffset,0))
	};

	//	ただし上記の設定値には、WorldやViewなどの3D空間から変換するための計算を一切しないため、
	//	スクリーン座標として描画される

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	cbuff.windowSize = SimpleMath::Vector4(Screen::WIDTH, Screen::HEIGHT, 1, 1);
	cbuff.diffuse = SimpleMath::Vector4(1, 1, 1, m_alphaValue);

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


	//	半透明描画指定
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	//	透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	深度バッファに書き込み参照する
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	//	カリングは左周り
	context->RSSetState(m_states->CullNone());

	//	シェーダをセットする
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//	ピクセルシェーダにテクスチャを登録する。
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());


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


