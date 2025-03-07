/*
	@file	Bounding.h
	@brief	デバッグ用カメラクラス
*/
#include "pch.h"
#include "Bounding.h"
#include "Libraries/Microsoft/DebugDraw.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include <cassert>


using namespace DirectX;


//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
WataLib::Bounding::Bounding(CommonResources* resources)
	:
	m_boundingBox{}
	, m_boundingSphere{}
	, m_batch{}
	, m_isBoxHit{ false }
	, m_isSphereHit{ false }
	,m_commonResources{resources}
{

}

WataLib::Bounding::~Bounding()
{



}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void WataLib::Bounding::Initialize()
{

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	// プリミティブバッチ、ベーシックエフェクトを準備する
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);
	m_effect = std::make_unique<BasicEffect>(device);
	m_effect->SetVertexColorEnabled(true);

	//// 入力レイアウトを作成する
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexPositionColor>(
			device,
			m_effect.get(),
			m_layout.ReleaseAndGetAddressOf()
		)
	);


}

void WataLib::Bounding::Update(DirectX::SimpleMath::Vector3 CenterPos)
{

	m_boundingSphere->Center = CenterPos;
	m_boundingBox->Center = CenterPos;

}

void WataLib::Bounding::Update(DirectX::SimpleMath::Vector3 CenterPos, DirectX::SimpleMath::Quaternion rotation)
{
	m_boundingSphere->Center = CenterPos;
	m_orientexBox->Center = CenterPos;

	m_orientexBox->Orientation = rotation;

}


void WataLib::Bounding::CreateBoundingBox(DirectX::SimpleMath::Vector3 CenterPos, DirectX::SimpleMath::Vector3 Extents)
{

	using namespace DirectX;

	m_boundingBox = std::make_unique<DirectX::BoundingBox>();
	
	m_boundingBox->Center = CenterPos;
	m_boundingBox->Extents = Extents;

}

void WataLib::Bounding::CreateBoundingOrientedBox(DirectX::SimpleMath::Vector3 CenterPos, DirectX::SimpleMath::Quaternion rotation, DirectX::SimpleMath::Vector3 Extents)
{

	m_orientexBox = std::make_unique<DirectX::BoundingOrientedBox>();

	m_orientexBox->Center = CenterPos;
	m_orientexBox->Extents = Extents;
	m_orientexBox->Orientation = rotation;

}

void WataLib::Bounding::Draw(const DirectX::SimpleMath::Vector3 CenterPos, DirectX::SimpleMath::Quaternion rotation, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{

	if (m_boundingSphere)
	{
		DrawBoundingSphere(CenterPos, view, projection);
	}

	if (m_boundingBox)
	{
		DrawBoundingBox(CenterPos, view, projection);
	}

	if(m_orientexBox)
	{
		DrawBoundingOrientedBox(CenterPos, rotation, view, projection);
	}

}



void WataLib::Bounding::CreateBoundingSphere(DirectX::SimpleMath::Vector3 CenterPos, float radius)
{
	using namespace DirectX;

	m_boundingSphere = std::make_unique<DirectX::BoundingSphere>();

	m_boundingSphere->Radius = radius;
	m_boundingSphere->Center = CenterPos;

}

void WataLib::Bounding::DrawBoundingBox(const DirectX::SimpleMath::Vector3 CenterPos, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	m_boundingBox->Center = CenterPos;
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	m_effect->SetView(view);
	m_effect->SetProjection(projection);
	m_effect->Apply(context);

	auto states = m_commonResources->GetCommonStates();
	context->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);	// 透過しない
	context->OMSetDepthStencilState(states->DepthDefault(), 0);			// Ｚバッファを使用する
	context->RSSetState(states->CullCounterClockwise());							// ポリゴンの両面を描画する
	context->IASetInputLayout(m_layout.Get());							// 入力レイアウトを設定する

	DirectX::XMVECTOR color = DirectX::Colors::Green;

	if (m_isBoxHit)
	{
		color = DirectX::Colors::Red;
	}

#ifdef _DEBUG
	// プリミティブ描画を開始する
	m_batch->Begin();

	// 境界ボックスを描画する
	DX::Draw(m_batch.get(), *m_boundingBox, color);
	// プリミティブ描画を終了する
	m_batch->End();

#endif

}

void WataLib::Bounding::DrawBoundingOrientedBox(const DirectX::SimpleMath::Vector3 CenterPos, DirectX::SimpleMath::Quaternion rotation, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	m_orientexBox->Center = CenterPos;
	m_orientexBox->Orientation = rotation;
	
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	m_effect->SetView(view);
	m_effect->SetProjection(projection);
	m_effect->Apply(context);

	auto states = m_commonResources->GetCommonStates();
	context->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);	// 透過しない
	context->OMSetDepthStencilState(states->DepthDefault(), 0);			// Ｚバッファを使用する
	context->RSSetState(states->CullCounterClockwise());							// ポリゴンの両面を描画する
	context->IASetInputLayout(m_layout.Get());							// 入力レイアウトを設定する

	DirectX::XMVECTOR color = DirectX::Colors::Green;

	if (m_isBoxHit)
	{
		color = DirectX::Colors::Red;
	}

#ifdef _DEBUG
	// プリミティブ描画を開始する
	m_batch->Begin();

	// 境界ボックスを描画する
	DX::Draw(m_batch.get(), *m_orientexBox, color);
	// プリミティブ描画を終了する
	m_batch->End();

#endif


}

void WataLib::Bounding::DrawBoundingSphere(const DirectX::SimpleMath::Vector3 CenterPos, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	m_boundingSphere->Center = CenterPos;
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	m_effect->SetView(view);
	m_effect->SetProjection(projection);
	m_effect->Apply(context);

	auto states = m_commonResources->GetCommonStates();
	context->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);	// 透過しない
	context->OMSetDepthStencilState(states->DepthDefault(), 0);			// Ｚバッファを使用する
	context->RSSetState(states->CullNone());							// ポリゴンの両面を描画する
	context->IASetInputLayout(m_layout.Get());							// 入力レイアウトを設定する

	DirectX::XMVECTOR color = DirectX::Colors::Yellow;

	if (m_isSphereHit)
	{
		color = DirectX::Colors::Red;
	}

#ifdef _DEBUG
	// プリミティブ描画を開始する
	m_batch->Begin();

	// 境界ボックスを描画する
	DX::Draw(m_batch.get(), *m_boundingSphere, color);
	// プリミティブ描画を終了する
	m_batch->End();

#endif

}



