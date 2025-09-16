/*
	クラス名     : WorldSpaceCanvas
	説明         :3D空間用のUI用Canvas
	補足・注意点 :
*/
#include "pch.h"
#include "WorldSpaceCanvas.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/Screen.h"
#include "GameBase/Actor.h"
#include "GameBase/Component/UI/ImageComponent.h"
#include "GameBase/Component/BaseComponents.h"
#include "GameBase/Shader/ShaderFactory.h"
#include "GameBase/Camera/Camera.h"

/// <summary>
/// インプットレイアウト
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> WorldSpaceCanvas::INPUT_LAYOUT =
{
	 { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
WorldSpaceCanvas::WorldSpaceCanvas(Scene* scene)
	:
	Canvas(scene, RenderType::WorldSpace)
	, m_vertexShader{}
	, m_pixelShader{}
	, m_geometryShader{}
	, m_CBuffer{}
	, m_inputLayout{}
	,m_isBillboard{true}
{

	using namespace DirectX;

	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();


	//	プリミティブバッチの作成
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);

	auto shaderFactory = ShaderFactory::GetInstance();



	m_inputLayout = shaderFactory->CreateInputLayout(device, INPUT_LAYOUT, "WorldSpaceUIVS.cso");

	//各シェーダーの作成
	m_vertexShader = shaderFactory->CreateVS(device,   "WorldSpaceUIVS.cso");
	m_pixelShader = shaderFactory->CreatePS(device,    "WorldSpaceUIPS.cso");
	m_geometryShader = shaderFactory->CreateGS(device, "WorldSpaceUIGS.cso");


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
WorldSpaceCanvas::~WorldSpaceCanvas()
{

}

/// <summary>
/// 描画
/// </summary>
void WorldSpaceCanvas::Render(const Camera& camera)
{

	for (auto& com : GetImageComponent())
	{

		if (!com->GetActive()) continue;

		//描画種類ごとに
		switch (com->GetRenderKinds())
		{
			case ImageComponent::RenderKinds::NORMAL:
				//通常描画
				NormalRender(camera,com);
				break;
			case ImageComponent::RenderKinds::CUSTOM:
				//登録された関数の呼び出し
				com->GetCustomRenderFunction()();
				break;
			default:
				break;
		}
	}

}

/// <summary>
/// 通常描画
/// </summary>
/// <param name="comp">コンポーネント</param>
void WorldSpaceCanvas::NormalRender(const Camera& camera,ImageComponent* comp)
{

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	auto states = CommonResources::GetInstance()->GetCommonStates();
	//頂点
	VertexPositionTexture vertex[1] = {
			VertexPositionTexture(comp->GetActor()->GetTransform()->GetWorldPosition(),Vector2(comp->GetTextureWidth(),comp->GetTextureHeight()))
	};

	Matrix view;

	if (m_isBillboard)
	{
		//ビルボードあり
		view = camera.GetViewMatrix().Invert();
	}
	else
	{
		//ビルボードなし
		view = Matrix::Identity;
	}
	

	//シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	WorldSpaceCanvas::ConstBuffer cbuff;
	cbuff.matView = camera.GetViewMatrix().Transpose();
	cbuff.matProj = camera.GetProjectionMatrix().Transpose();
	cbuff.matWorld = view.Transpose() ;



	cbuff.Position = Vector4(0,1, 0, 0);
	cbuff.Size = Vector4(comp->GetWidth(), comp->GetHeight(), 1, 1);
	cbuff.Rotate = Vector4(comp->GetAngle(), 0, 0, 0);
	cbuff.Color = comp->GetColor();
	cbuff.CutRange = comp->GetCutRange();
	cbuff.ViewRange = comp->GetViewRange();
	cbuff.FillAmount = comp->GetFillAmount();



	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);
	//	半透明描画指定
	ID3D11BlendState* blendstate = states->NonPremultiplied();

	//	透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	深度バッファに書き込み参照する
	context->OMSetDepthStencilState(states->DepthNone(), 0);

	context->RSSetState(states->CullNone());

	//	シェーダをセットする
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//	ピクセルシェーダにテクスチャを登録する。
	context->PSSetShaderResources(0, 1, comp->GetTexture().GetAddressOf());

	//	インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	//	板ポリゴンを描画
	m_batch->Begin();
	//m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex, 1);
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], ARRAYSIZE(vertex));
	m_batch->End();

	//	シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);


}

