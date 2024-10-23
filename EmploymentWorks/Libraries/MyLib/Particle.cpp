#include "pch.h"
#include "Particle.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "BinaryFile.h"



using namespace DirectX;
using namespace DirectX::SimpleMath;

const float SCALE = 3.0f;

const std::vector<D3D11_INPUT_ELEMENT_DESC> Particle::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0,							 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	0, sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


Particle::Particle()
	:
	m_commonResources{}
	,m_time{}
	,m_inputLayout{}
	,m_scale{}
	,m_alpha{}
	,m_angleX{}
	,m_textureHeight{}
	,m_textureWidth{}
	,m_state{}
{

}

Particle::~Particle()
{

}

// 初期化
void Particle::Initialize(CommonResources* resourece)
{

	m_commonResources = resourece;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	BinaryFile VS = BinaryFile::LoadFile(L"Resources/Shaders/Particle/ParticleVS.cso");
	BinaryFile PS = BinaryFile::LoadFile(L"Resources/Shaders/Particle/ParticlePS.cso");

	//	インプットレイアウトの作成
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VS.GetData(), VS.GetSize(),
		m_inputLayout.ReleaseAndGetAddressOf());


	DX::ThrowIfFailed(
		device->CreateVertexShader(
			VS.GetData(),
			VS.GetSize(),
			nullptr,
			m_vertexShader.ReleaseAndGetAddressOf())
	);


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

	//画像の読み込み
	DirectX::CreateWICTextureFromFile(device, L"Resources/Textures/ExplosionEffects.png", m_res.ReleaseAndGetAddressOf(), m_texture.ReleaseAndGetAddressOf());
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;
	DX::ThrowIfFailed(m_res.As(&tex));

	//	読み込んだ画像の情報を取得する
	D3D11_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);

	//	読み込んだ画像のサイズを取得する
	m_textureWidth = desc.Width;
	m_textureHeight = desc.Height;

	m_Batch = std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);

	m_position = Vector3(4, 0, 0);
	m_alpha = 1.0f;

	m_time = 0;
	float a = SCALE;

	//画像の縦横の長さから割合を求める
	float aspectRatio = static_cast<float>(m_textureWidth) / static_cast<float>(m_textureHeight);
	//Xを割合に基づいて変更
	m_scale = Vector3(aspectRatio * a, a, a);

	m_state = State::None;
}

// 更新
void Particle::Update(float elapsedTime)
{
	//m_time += 0.1f * elapsedTime;
	m_scale.x += 4.0f * elapsedTime;
	m_scale.y += 4.0f * elapsedTime;

	m_scale.x = std::min(m_scale.x, 2.0f);
	m_scale.y = std::min(m_scale.y, 2.0f);
	//大きさが最大になったら
	if (m_scale.x == 2.0f)
	{
		m_alpha -= 1.5f * elapsedTime;
	}

	//透明度が０以下になれば
	if (m_alpha <= 0)
	{
		m_state = State::None;
	}
}

// 描画
void Particle::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	VertexPositionTexture vertex[4] = {
		//	頂点情報													                                              UV情報
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

	ConstBuffer cbuff;
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.matWorld = m_world.Transpose();
	cbuff.diffuse = Vector4(1, 1, 1, m_alpha);
	cbuff.time = Vector4(m_time, 1, 1, 1);

	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//	画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);


	context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);

	//	深度バッファに書き込み参照する
	context->OMSetDepthStencilState(states->DepthDefault(), 0);


	//	カリングはなし
	context->RSSetState(states->CullNone());


	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);




	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());


	context->IASetInputLayout(m_inputLayout.Get());




	m_Batch->Begin();
	m_Batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	m_Batch->End();

	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

// 終了処理
void Particle::Finalize()
{
}

void Particle::Create(DirectX::SimpleMath::Vector3 Pos)
{
	//使用に変更
	m_state = State::Using;
	//
	m_position = Pos;

	m_alpha = 1.0f;

	m_time = 0;
	float a = SCALE;

	//画像の縦横の長さから割合を求める
	float aspectRatio = static_cast<float>(m_textureWidth) / static_cast<float>(m_textureHeight);
	//Xを割合に基づいて変更
	m_scale = Vector3(aspectRatio * a, a, a);

}


