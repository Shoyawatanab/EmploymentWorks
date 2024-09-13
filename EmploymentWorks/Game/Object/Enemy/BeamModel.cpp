/*
	@file	BeamModel.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BeamModel.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>



//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
BeamModel::BeamModel()
	:
	m_commonResources{},
	m_model{}
	,m_scale{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
BeamModel::~BeamModel()
{
	// do nothing.
}


//ディープコピー用コンストラクタ
BeamModel::BeamModel(BeamModel& other)
{

	m_commonResources = other.m_commonResources;
	m_position = other.m_position;
	m_scale = other.m_scale;
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();




	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Beam.cmo", *fx);

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void BeamModel::Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position, float scale)
{
	using namespace DirectX::SimpleMath;


	assert(resources);
	m_commonResources = resources;
	m_position = position;
	m_scale = scale;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();




	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Beam.cmo", *fx);


}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void BeamModel::Update(float elapsedTime, DirectX::SimpleMath::Quaternion cameraRotation)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	UNREFERENCED_PARAMETER(cameraRotation);

	using namespace DirectX;
	using namespace DirectX::SimpleMath;


}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void BeamModel::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	using namespace DirectX::SimpleMath;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();


	// ワールド行列を更新する
	Matrix world = Matrix::CreateScale(m_scale);
	world *= Matrix::CreateTranslation(m_position);


	// モデルを描画する
	m_model->Draw(context, *states, world, view, projection);

	

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void BeamModel::Finalize()
{
	// do nothing.
}


