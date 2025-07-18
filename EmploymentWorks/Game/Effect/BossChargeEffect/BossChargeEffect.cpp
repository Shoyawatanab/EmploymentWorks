/*
	クラス名     : BossChargeEffect
	説明         : ボスのジャンプ時のチャージエフェクト
	補足・注意点 :
*/
#include "pch.h"
#include "BossChargeEffect.h"
#include "GameBase/Component/Effect/EffectComponent.h"
#include "GameBase/Component/Transform/Transform.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/Camera/Camera.h"
#include "GameBase/GameResources.h"
#include "Game/Effect/ParticleUtility.h"
#include "GameBase/Shader/ShaderFactory.h"



/// <summary>
/// インプットレイアウト
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> BossChargeEffect::INPUT_LAYOUT =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,                                                                           D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	sizeof(DirectX::SimpleMath::Vector3),                                        D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,	     0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};



/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
BossChargeEffect::BossChargeEffect(Scene* scene)
	:
	Actor(scene)
	,m_inputLayout{}
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	AddComponent<EffectComponent>(this, std::bind(&BossChargeEffect::Render, this, std::placeholders::_1));



	using namespace DirectX;

	//デバイスの取得
	ID3D11Device1* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	//コンテキストの取得
	ID3D11DeviceContext1* context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//	シェーダーの作成
	CreateShader();

	//画像の取得
	m_texture.push_back(GameResources::GetInstance()->GetTexture("da"));

	//	プリミティブバッチの作成
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);
	//コモンステートの作成
	m_states = std::make_unique<CommonStates>(device);

	SetActive(false);

}

/// <summary>
/// デストラクタ
/// </summary>
BossChargeEffect::~BossChargeEffect()
{
}

/// <summary>
/// 個別アップデート
/// </summary>
/// <param name="deltaTime">経過時間</param>
void BossChargeEffect::UpdateActor(const float& deltaTime)
{

	//ユーティリティの更新
	for (auto it = m_ChargeEffectUtility.begin(); it != m_ChargeEffectUtility.end(); )
	{
		if (!it->Update(deltaTime)) {
			it = m_ChargeEffectUtility.erase(it);  // 削除後の新しいイテレーターを取得
		}
		else {
			++it;  // 削除しなかった場合は次の要素へ
		}
	}

	//0.5秒ごとにエフェクトの作成
	if (fmod(m_time, GENERATION_INTERVAL) < deltaTime)
	{
		CreateUtility();
	}

	//終了かどうか
	if (m_time >= GENERATION_TIME)
	{
		//初期化
		m_time = 0.0f;
		SetActive(false);
	}

	//経過時間の加算
	m_time += deltaTime;

}



/// <summary>
/// 描画
/// </summary>
/// <param name="camera">カメラ</param>
void BossChargeEffect::Render(const Camera& camera)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//コンテキストの取得
	ID3D11DeviceContext1* context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	auto view = camera.GetViewMatrix();
	auto projection = camera.GetProjectionMatrix();

	//	登録されている頂点をリセット
	m_vertices.clear();
	for (ParticleUtility& li : m_ChargeEffectUtility)
	{
		VertexPositionColorTexture vPCT;
		vPCT.position = XMFLOAT3(li.GetPosition());
		//	テクスチャの色
		vPCT.color = XMFLOAT4(li.GetNowColor());
		//	現在のテクスチャのスケールを「XMFLOAT2」のXに入れる。
		vPCT.textureCoordinate = XMFLOAT2(li.GetNowScale().x, 0.0f);

		m_vertices.push_back(vPCT);
	}

	//	表示する点がない場合は描画を終わる
	if (m_vertices.empty())
	{
		return;
	}


	// ビルボードマトリックスを計算する
	m_billboard = view.Invert();
	m_billboard._41 = 0.0f;
	m_billboard._42 = 0.0f;
	m_billboard._43 = 0.0f;

	//シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	cbuff.matView = view.Transpose();
	cbuff.matProj = projection.Transpose();
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

	m_batch->Begin();

	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices[0], m_vertices.size());

	m_batch->End();

	//	シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);


}

/// <summary>
/// アクティブ状態になった時
/// </summary>
void BossChargeEffect::OnEnable()
{
	m_time = 0.0f;
}

void BossChargeEffect::CreateShader()
{
	ID3D11Device1* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	auto shaderFactory = ShaderFactory::GetInstance();

	//各シェーダーの作成
	m_vertexShader = shaderFactory->CreateVS(device, "ParticleVS.cso");
	m_pixelShader = shaderFactory->CreatePS(device, "ParticlePS.cso");
	m_geometryShader = shaderFactory->CreateGS(device, "ParticleGS.cso");

	m_inputLayout = shaderFactory->CreateInputLayout(device, INPUT_LAYOUT, "ParticleVS.cso");


	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);

}

void BossChargeEffect::CreateUtility()
{

	using namespace DirectX::SimpleMath;

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

		ParticleUtility pU(
			3.0f,																			//	生存時間(s)
			pos + GetTransform()->GetWorldPosition(),				                                                        //	基準座標
			velocity,		//	速度
			Vector3(0.5f, 0.0f, 0.5f),														//	加速度
			scale,                                                      //	初期スケール
			scale,							                  //	最終スケール
			Color(1.f, 1.f, 1.f, 1.f),											// 初期カラー、
			Color(1.f, 1.f, 1.f, -1.f)										   //	最終カラー
		);

		m_ChargeEffectUtility.push_back(pU);
	}

}
