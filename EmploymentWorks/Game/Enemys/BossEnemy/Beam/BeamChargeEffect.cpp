/*
	@file	BeamChargeEffect.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BeamChargeEffect.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/WataLib/GameResources.h"
#include <cassert>
#include "Libraries/MyLib/BinaryFile.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "Game/Params.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



const std::vector<D3D11_INPUT_ELEMENT_DESC> BeamChargeEffect::INPUT_LAYOUT =
{
	{ "POSITION",    0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT",     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",       0, DXGI_FORMAT_R8G8B8A8_UNORM,     0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// コンストラクタ
/// </summary>
BeamChargeEffect::BeamChargeEffect()
	:
	m_commonResources{},
	m_model{}
	,m_vertexShader{}
	,m_pixelShader{}
	,m_inputLayout{}
	,m_CBuffer{}
	,m_position{}
	,m_scale{}
	,m_initialPosition{}
	,m_initialScale{}
	,m_initialRotate{}
	,m_beam{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
BeamChargeEffect::~BeamChargeEffect()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resoure">共通リソース</param>
/// <param name="position">座標</param>
/// <param name="rotate">回転</param>
void BeamChargeEffect::Initialize(CommonResources* resoure,DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotate)
{
	m_commonResources = resoure;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	// モデルを読み込む
	m_model = m_commonResources->GetGameResources()->GetModel("BeamChargeEffect");

	m_position = position;

	//ビームの太さ
	float a = 0.1f;

	m_initialScale = Vector3(a, a, a);

	m_scale = m_initialScale;

	m_initialRotate = rotate;

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BeamChargeEffect::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	Vector3 beamPosition = m_beam->GetPosition();

	//中心に向かって移動させる
	Vector3 direction = Vector3::Zero - m_position;
	direction.Normalize();

	direction *= elapsedTime * Params::BOSSENEMY_BEAM_CHARGE_EFFECT_MOVE_TIME;

	m_position += direction;

	float distance = Vector3::Distance(beamPosition, m_position);


	if (distance < 0.1f)
	{
		m_beam->RegistrationDeleteParticle(this);
	}

}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void BeamChargeEffect::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();



	// ワールド行列を更新する
	Matrix world = Matrix::Identity;
	world *= Matrix::CreateScale(m_scale);
	world *= Matrix::CreateFromQuaternion(m_initialRotate);
	world *= Matrix::CreateTranslation(m_position);
	world *= Matrix::CreateFromQuaternion(m_beam->GetRotation());
	world *= Matrix::CreateTranslation(m_beam->GetPosition());

	//モデルを描画する
	m_model->Draw(context, *states, world, view, projection, false, [&]()
		{
		});

	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void BeamChargeEffect::Finalize()
{
	// do nothing.
}

/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="beam">ビーム</param>
void BeamChargeEffect::AddPointer(Beam* beam)
{
	m_beam = beam;

}

