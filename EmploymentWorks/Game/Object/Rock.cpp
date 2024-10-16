/*
	@file	Rock.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Rock.h"
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

const DirectX::SimpleMath::Vector3 POS(0.0f, 0.0f, 0.0f);
const float SCALE(8.0f);

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Rock::Rock()
	:
	m_commonResources{},
	m_model{},
	m_scale{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Rock::~Rock()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Rock::Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 Scale, DirectX::SimpleMath::Vector3 Rotate)
{
	using namespace DirectX::SimpleMath;
	assert(resources);
	m_commonResources = resources;
	m_position = position;
	m_scale = Scale;
	m_rotate = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(Rotate.x), DirectX::XMConvertToRadians(Rotate.y), DirectX::XMConvertToRadians(Rotate.z));


	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Rock.cmo", *fx);

	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position,m_scale);
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, 40.0f);

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Rock::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Rock::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	using namespace DirectX::SimpleMath;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();


	// ワールド行列を更新する
	Matrix world = Matrix::CreateScale(m_scale);
	world *= Matrix::CreateFromQuaternion(m_rotate);
	world *= Matrix::CreateTranslation(m_position);
	// モデルを描画する
	m_model->Draw(context, *states, world, view, projection);
	//m_bounding->DrawBoundingSphere(POS, view, projection);
	m_bounding->DrawBoundingBox(m_position, view, projection);



}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Rock::Finalize()
{
	// do nothing.
}


void Rock::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
}


void Rock::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(PartnerTag);
	UNREFERENCED_PARAMETER(Pos);
}

