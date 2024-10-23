/*
	@file	Artillery.cpp
	@brief	
*/
#include "pch.h"
#include "Artillery.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/DetectionCollision/CollisionManager.h"
#include "Libraries/MyLib/Bounding.h"

#include "Game/Object/Gimmick/Artillery/ArtilleryBase.h"
#include "Game/Object/Gimmick/Artillery/ArtilleryTurret.h"

const float SCALE(8.6f);

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Artillery::Artillery()
	:
	m_commonResources{}
	,m_scale{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Artillery::~Artillery()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Artillery::Initialize(CommonResources* resources, PlayScene* playScene, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 Scale, DirectX::SimpleMath::Vector3 Rotate, float BoundingSphereRadius)
{
	using namespace DirectX::SimpleMath;
	using namespace DirectX;
	assert(resources);
	m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	//auto states = m_commonResources->GetCommonStates();



	m_position = position;
	m_scale = Scale;
	m_rotate = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(Rotate.x), DirectX::XMConvertToRadians(Rotate.y), DirectX::XMConvertToRadians(Rotate.z));





	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position, m_scale * 0.7f);
	m_bounding->CreateBoundingSphere(m_commonResources,m_position, BoundingSphereRadius );

	m_base = std::make_unique<ArtilleryBase>();
	m_base->Initialize(m_commonResources, m_position, m_scale, Quaternion::Identity);

	m_turret = std::make_unique<ArtilleryTurret>();
	m_turret->Initialize(m_commonResources,playScene, m_position, m_scale, m_rotate);


	/*
	ビルボードの描画に関連するオブジェクトを設定する
*/
// ベーシックエフェクトを作成する
	m_basicEffect = std::make_unique<BasicEffect>(device);
	m_basicEffect->SetTextureEnabled(true);	// テクスチャを使用する
	/*
		・ベーシックエフェクトの「Set○○Enabled」は必要なものだけ「true」に設定する
		・不要なものは指定しなくてよい（デフォルトで「false」に設定される）
	*/

	// 入力レイアウトを作成する
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexPositionTexture>(
			device,
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()
		)
	);

	// プリミティブバッチを作成する
	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);
	/*
		・「ポリゴンの頂点情報」「入力レイアウトの頂点情報」「プリミティブバッチの頂点情報」を統一する
	*/

	// 画像をロードする
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(
			device,
			L"Resources/Textures/ArtilleryIcon.png",
			nullptr,
			m_texture.ReleaseAndGetAddressOf()
		)
	);

	DirectX::SimpleMath::Vector3 scale = Vector3(2, 2, 0);


	// ビルボードの頂点情報を設定する：今回は「VertexPositionTexture」を使用する
	m_vertices[0] = { Vector3(-0.5f * scale.x, 0.5f * scale.y,0.0f),Vector2(0.0f,0.0f) };	// 左上
	m_vertices[1] = { Vector3(0.5f * scale.x, 0.5f * scale.y,0.0f),Vector2(1.0f,0.0f) };	// 右上
	m_vertices[2] = { Vector3(-0.5f * scale.x,-0.5f * scale.y,0.0f),Vector2(0.0f,1.0f) };	// 左下
	m_vertices[3] = { Vector3(0.5f * scale.x,-0.5f * scale.y,0.0f),Vector2(1.0f,1.0f) };	// 右下





}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Artillery::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	m_base->Update(elapsedTime);

	m_turret->Update(elapsedTime);

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Artillery::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	using namespace DirectX::SimpleMath;


	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();


	// ワールド行列を更新する
	Matrix world = Matrix::CreateScale(m_scale);
	world *= Matrix::CreateFromQuaternion(m_rotate);
	world *= Matrix::CreateTranslation(m_position);



	m_bounding->DrawBoundingSphere(m_position, view, projection);
	m_bounding->DrawBoundingBox(m_position, view, projection);

	m_base->Render(view, projection);
	m_turret->Render(view, projection);


	// ビルボードをアフィン行列を作る
	Matrix billboardMatrix = view.Invert();
	billboardMatrix._41 = 0.0f;
	billboardMatrix._42 = 0.0f;
	billboardMatrix._43 = 0.0f;
	/*
		■ビルボード行列の求め方
		・使用するビュー行列の逆行列を求める
		・平行移動分をキャンセルする
	*/

	// ビルボードの（原点からの）平行移動量
	Vector3 billboardTranslationValue{ 0.0f, 1.0f, 0.0f };

	// ビルボードをアフィン変換する
	Matrix worldBillboard{};
	worldBillboard = billboardMatrix;										// A
	worldBillboard *= Matrix::CreateTranslation(m_position + Vector3(0,4,0));	// B
	/*
		■ビルボードとワールド行列
		・まず、ワールド行列にビルボード行列を代入する::A
		・次に、ビルボードの高さを調整する::B
		・残りはサイコロのアフィン変換を参考に変換行列を計算する

		■サイコロの回転とビルボードの回転の相関関係
		・①の回転は③④の回転に影響しない→１倍
		・②の回転は③④の回転に影響する→それぞれ同率倍にする
	*/

	// ポリゴンを描画するために各種パラメータを設定する
	context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);	// Tridentロゴは「NonPremultiplied」
	context->OMSetDepthStencilState(states->DepthDefault(), 0);					// 深度情報のreadとwrite
	context->RSSetState(states->CullCounterClockwise());						// ポリゴンの裏面は描画しない
	context->IASetInputLayout(m_inputLayout.Get());								// 適切な入力レイアウトを指定する

	m_basicEffect->SetWorld(worldBillboard);	// ワールド行列を指定する
	m_basicEffect->SetView(view);				// ビュー行列を指定する
	m_basicEffect->SetProjection(projection);	// 射影行列を指定する
	m_basicEffect->SetTexture(m_texture.Get());	// テクスチャを指定する
	m_basicEffect->Apply(context);				// ベーシックエフェクトの変更を適用する

	// ビルボードを描画する
	m_primitiveBatch->Begin();
	m_primitiveBatch->DrawQuad(m_vertices[0], m_vertices[1], m_vertices[3], m_vertices[2]);
	m_primitiveBatch->End();

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Artillery::Finalize()
{
	// do nothing.
}


void Artillery::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);

	//Turreの中にあるBulletの当たり判定の登録　Turretに判定はない
	m_turret->RegistrationCollionManager(collsionManager);
}



void Artillery::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(PartnerTag);
	UNREFERENCED_PARAMETER(Pos);

	switch (PartnerTag)
	{
		case CollsionObjectTag::Boomerang:
			m_turret->Shot();
			break;
		default:
			break;
	}

}

