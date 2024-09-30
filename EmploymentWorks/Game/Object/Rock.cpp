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
#include "FrameWork/Resources.h"
#include "Libraries/MyLib/CollisionMesh.h"


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
void Rock::Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 Extens, float Scale)
{
	using namespace DirectX::SimpleMath;
	assert(resources);
	m_commonResources = resources;
	m_position = position;
	m_scale = Scale;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();


	// モデルを読み込む
	//m_model = Resources::GetInstance()->GetRockModel();

		// リソースディレクトリを設定する
	std::unique_ptr<DirectX::EffectFactory> rockFx = std::make_unique<DirectX::EffectFactory>(device);
	rockFx->SetDirectory(L"Resources/Models");
	// 「岩」モデルをロードする
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Rock.cmo", *rockFx);


	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position, Extens);
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, 4.0f);

	// コリジョンメッシュを生成する
	m_collisionMesh = std::make_unique<mylib::CollisionMesh>();
	//岩のメッシュの読み込み
	m_collisionMesh->Initialize(device, context, L"Rock", m_position, m_scale);


}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Rock::Update(float elapsedTime, DirectX::SimpleMath::Quaternion cameraRotation)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	UNREFERENCED_PARAMETER(cameraRotation);

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
	world *= Matrix::CreateTranslation(m_position);
	// モデルを描画する
	m_model->Draw(context, *states, world, view, projection);
	m_bounding->DrawBoundingSphere(POS, view, projection);
	//m_bounding->DrawBoundingBox(m_position, view, projection);


	// メッシュを描画する
	m_collisionMesh->Draw(context, states, view, projection);


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

