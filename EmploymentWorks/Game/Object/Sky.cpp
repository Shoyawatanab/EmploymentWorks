/*
	@file	Sky.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Sky.h"
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
Sky::Sky()
	:
	m_commonResources{},
	m_model{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Sky::~Sky()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Sky::Initialize(CommonResources* resources)
{
	using namespace DirectX::SimpleMath;
	assert(resources);
	m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Sky.cmo", *fx);


}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Sky::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Sky::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	using namespace DirectX::SimpleMath;
	using namespace DirectX;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();


	// モデルのエフェクト情報を更新する
	m_model->UpdateEffects([](DirectX::IEffect* effect)
		{
			// ベーシックエフェクトを設定する
			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				// 個別のライトをすべて無効化する
				basicEffect->SetLightEnabled(0, false);
				basicEffect->SetLightEnabled(1, false);
				basicEffect->SetLightEnabled(2, false);

				// 環境光も無効化する
				basicEffect->SetAmbientLightColor(Colors::Black);

				// モデルを自発光させる
				basicEffect->SetEmissiveColor(Colors::White);
			}
		}
	);

	// ワールド行列を更新する
	Matrix world = Matrix::Identity;

	// モデルを描画する
	m_model->Draw(context, *states, world, view, projection);



}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Sky::Finalize()
{
	// do nothing.
}


