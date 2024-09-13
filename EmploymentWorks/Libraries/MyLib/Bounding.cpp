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


//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Bounding::Bounding()
	:
	m_boundingBox{}
	, m_boundingSphere{}
	, m_commonResources{}
	, m_batch{}
	, m_isBoxHit{ false }
	, m_isSphereHit{ false }
{

}

//void Bounding::Render(const DirectX::SimpleMath::Vector3 CenterPos, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
//{
//	assert(view);
//
//
//}

void Bounding::CreateBoundingBox(CommonResources* resources, DirectX::SimpleMath::Vector3 CenterPos, DirectX::SimpleMath::Vector3 Extents)
{

	using namespace DirectX;


	m_commonResources = resources;
	m_boundingBox.Center = CenterPos;
	m_boundingBox.Extents = Extents;

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


void Bounding::CreateBoundingSphere(CommonResources* resources, DirectX::SimpleMath::Vector3 CenterPos, float radius)
{
	using namespace DirectX;

	m_commonResources = resources;
	m_boundingSphere.Radius = radius;
	m_boundingSphere.Center = CenterPos;

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

void Bounding::DrawBoundingBox(const DirectX::SimpleMath::Vector3 CenterPos, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	m_boundingBox.Center = CenterPos;
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
	DX::Draw(m_batch.get(), m_boundingBox, color);
	// プリミティブ描画を終了する
	m_batch->End();

#endif

}

void Bounding::DrawBoundingSphere(const DirectX::SimpleMath::Vector3 CenterPos, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	m_boundingSphere.Center = CenterPos;
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
	DX::Draw(m_batch.get(), m_boundingSphere, color);
	// プリミティブ描画を終了する
	m_batch->End();

#endif

}

void Bounding::DrawBoundingSphere(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
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
	DX::Draw(m_batch.get(), m_boundingSphere, color);
	// プリミティブ描画を終了する
	m_batch->End();

#endif

}

