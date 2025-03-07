#include "pch.h"
#include "CircleParticle.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/BinaryFile.h"



using namespace DirectX;
using namespace DirectX::SimpleMath;

//インプットレイアウト
const std::vector<D3D11_INPUT_ELEMENT_DESC> CircleParticle::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0,							 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	0, sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

float Lerp(const float& start, const float& end, const float& t)
{
	return (1.0f - t) * start + t * end;
}


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resourece">共通リソース</param>
CircleParticle::CircleParticle(CommonResources* resourece)
	:
	m_commonResources{resourece}
	,m_Batch{}
	,m_time{}
	,m_inputLayout{}
	,m_scale{}
	,m_position{}
	,m_alpha{}
	,m_vertexShader{}
	,m_pixelShader{}
	,m_CBuffer{}
	,m_world{}

{

}

/// <summary>
/// デストラクタ
/// </summary>
CircleParticle::~CircleParticle()
{

}

/// <summary>
/// 初期化
/// </summary>
void CircleParticle::Initialize()
{


	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	//シェーダーファイルの読み込み
	BinaryFile VS = BinaryFile::LoadFile(L"Resources/Shaders/CircleParticleVS.cso");
	BinaryFile PS = BinaryFile::LoadFile(L"Resources/Shaders/CircleParticlePS.cso");

	//	インプットレイアウトの作成
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VS.GetData(), VS.GetSize(),
		m_inputLayout.ReleaseAndGetAddressOf());

	//頂点シェーダーを作成し格納
	DX::ThrowIfFailed(
		device->CreateVertexShader(
			VS.GetData(),
			VS.GetSize(),
			nullptr,
			m_vertexShader.ReleaseAndGetAddressOf())
	);

	//ピクセルシェーダーを作成し格納
	DX::ThrowIfFailed(
		device->CreatePixelShader(
			PS.GetData(),
			PS.GetSize(),
			nullptr,
			m_pixelShader.ReleaseAndGetAddressOf())
	);

	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);


	//プリミティブバッチの作成
	m_Batch = std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);

	//透明度の初期化
	m_alpha = 1.0f;
	//経過時間の初期化
	m_time = 0;
	//Xを割合に基づいて変更
	m_scale = DirectX::SimpleMath::Vector3::One;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>ture 終了  false　継続　</returns>
bool CircleParticle::Update(float elapsedTime)
{

	//経過時間の加算
	m_time += elapsedTime;

	//終了したら
	if (m_time >= 2)
	{
		return true;
	}

	return false ; 

}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void CircleParticle::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	//頂点データ
	VertexPositionTexture circleVertex[4] = {
		VertexPositionTexture(SimpleMath::Vector3(-0.5f,-0.5f ,0.0f), SimpleMath::Vector2(0.0f, 0.0f)),
		VertexPositionTexture(SimpleMath::Vector3(0.5f ,-0.5f ,0.0f), SimpleMath::Vector2(1.0f, 0.0f)),
		VertexPositionTexture(SimpleMath::Vector3(0.5f,0.5f  ,0.0f ), SimpleMath::Vector2(1.0f, 1.0f)),
		VertexPositionTexture(SimpleMath::Vector3(-0.5f,0.5f ,0.0f ), SimpleMath::Vector2(0.0f, 1.0f)),
	};

	//ワールドの計算
	m_world = Matrix::CreateScale(m_scale);
	//ビルボード処理
	m_world *= view.Invert();
	m_world._41 = 0.0f;
	m_world._42 = 0.0f;
	m_world._43 = 0.0f;
	m_world *= Matrix::CreateTranslation(m_position);

	//バッファの作成
	ConstBuffer cbuff;
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.matWorld = m_world.Transpose();
	cbuff.diffuse = Vector4(1, 1, 1, m_alpha);
	cbuff.time = Vector4(m_time, 1, 1, 1);

	//バッファの更新
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//各シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//	画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//ブレンドの設定
	context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);

	//	深度バッファに書き込み参照
	context->OMSetDepthStencilState(states->DepthDefault(), 0);

	//	カリング状態の設定
	context->RSSetState(states->CullNone());

	//シェーダーのセット
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);
	//ピクセルシェーダーに画像を登録
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());
	//インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());
	//板ポリゴンの描画
	m_Batch->Begin();
	m_Batch->DrawQuad(circleVertex[0], circleVertex[1], circleVertex[2], circleVertex[3]);
	m_Batch->End();

	//シェーダーの解除
	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

// 終了処理
void CircleParticle::Finalize()
{
}


