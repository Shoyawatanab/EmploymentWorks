#include "pch.h"
#include "ImageComponent.h"
#include "GameBase/Actor.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Managers.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/GameResources.h"
#include "GameBase/Shader/ShaderFactory.h"
#include "Libraries/MyLib/BinaryFile.h"
#include "GameBase/Screen.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// インプットレイアウト
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> ImageComponent::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,                                                                           D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3),                                        D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,       0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


ImageComponent::ImageComponent(Actor* owner, std::string textureName)
	:
	Component(owner)
	,m_texture{}
	,m_CBuffer{}
	,m_inputLayout{}
	, m_vertexShader{}
	,m_pixelShader{}
	,m_geometryShader{}
	,m_textureHeight{}
	,m_textureWidth{}
	,m_renderRatio{1.0f}
	,m_renderRatioOffset{}
	, m_alphaValue{1.0f}
{

	using namespace DirectX;


	//マネージャーに追加
	GetActor()->GetScene()->GetRenderMangaer()->AddUserInterface(this);

	LoadTexture(textureName);


	//シェーダーの作成
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();


	auto shaderFactory = ShaderFactory::GetInstance();

	//各シェーダーの作成
	m_vertexShader = shaderFactory->CreateVS(device, "UIVS.cso");
	m_pixelShader = shaderFactory->CreatePS(device, "UIPS.cso");
	m_geometryShader = shaderFactory->CreateGS(device, "UIGS.cso");

	m_inputLayout = shaderFactory->CreateInputLayout(device, INPUT_LAYOUT, "UIVS.cso");


	//	プリミティブバッチの作成
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);


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
/// デストラクタ
/// </summary>
ImageComponent::~ImageComponent()
{
}


void ImageComponent::Render()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	
	auto states = CommonResources::GetInstance()->GetCommonStates();


	// 頂点情報
	// Position.xy	:拡縮用スケール
	// Position.z	:アンカータイプ(0～8)の整数で指定
	// Color.xy　	:アンカー座標(ピクセル指定:1280 ×720)
	// Color.zw		:画像サイズ
	// Tex.xy		:ウィンドウサイズ（バッファも同じ。こちらは未使用）
	VertexPositionColorTexture vertex[1] = {
		VertexPositionColorTexture(
			 Vector3(GetActor()->GetTransform()->GetWorldScale().x, GetActor()->GetTransform()->GetWorldScale().y, ANCHOR::MIDDLE_CENTER)
			,Vector4(GetActor()->GetTransform()->GetWorldPosition().x, GetActor()->GetTransform()->GetWorldPosition().y, static_cast<float>(m_textureWidth), static_cast<float>(m_textureHeight))
			,Vector2(m_renderRatio - m_renderRatioOffset,0))
	};


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

void ImageComponent::LoadTexture(std::string textureName)
{

	//画像の読み込み
	m_texture = CommonResources::GetInstance()->GetGameResources()->GetTexture(textureName);

	//シェーダーリソースビューから画像情報の取得
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	m_texture->GetResource(&resource);

	//リソースをTexture2Dにキャスト
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;
	DX::ThrowIfFailed(resource.As(&tex));

	//画像情報を取得
	D3D11_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);

	//画像のサイズを取得
	m_textureWidth = desc.Width;
	m_textureHeight = desc.Height;
}


