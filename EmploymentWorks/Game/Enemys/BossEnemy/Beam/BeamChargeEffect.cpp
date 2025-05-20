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
/// <param name="resoure">共通リソース</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotate">回転</param>
BeamChargeEffect::BeamChargeEffect(CommonResources* resoure, DirectX::SimpleMath::Vector3 scale,DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotate)
	:
	BaseEntity(resoure, scale,position,rotate)
	,m_model{}
	,m_vertexShader{}
	,m_pixelShader{}
	,m_inputLayout{}
	,m_CBuffer{}
	,m_initialPosition{}
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
void BeamChargeEffect::Initialize()
{

	// モデルを読み込む
	m_model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BeamChargeEffect");



}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BeamChargeEffect::Update(const float& elapsedTime)
{

	using namespace DirectX::SimpleMath;

	//オブジェクトか更新が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}


	Vector3 beamPosition = m_beam->GetPosition();

	Vector3 position =  BaseEntity::GetLocalPosition();

	//中心に向かって移動させる
	Vector3 direction = Vector3::Zero - position;
	direction.Normalize();

	direction *= elapsedTime * Params::BOSSENEMY_BEAM_CHARGE_EFFECT_MOVE_TIME;

	position += direction;

	BaseEntity::SetLocalPosition(position);

	float distance = Vector3::Distance(beamPosition, BaseEntity::GetPosition());


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
	using namespace DirectX::SimpleMath;
	
	//オブジェクトか描画が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsRenderActive())
	{
		return;
	}


	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();



	// ワールド行列を更新する
	BaseEntity::Render(view,projection);

	//モデルを描画する
	m_model->Draw(context, *states, BaseEntity::GetWorldMatrix(), view, projection, false, [&]()
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

/// <summary>
/// 無効になったら
/// </summary>
void BeamChargeEffect::OnDisable()
{
	m_beam->RegistrationDeleteParticle(this);

}

