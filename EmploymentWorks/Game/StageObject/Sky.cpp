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
#include "Libraries/WataLib/GameResources.h"
#include <cassert>

using namespace DirectX;
using namespace DirectX::SimpleMath;


//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Sky::Sky(CommonResources* resources
	, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation)
	:
	m_model{}
	, BaseEntity(resources,scale,position,rotation)
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Sky::~Sky()
{
	// do nothing.
}

void Sky::Initialize()
{

	BaseEntity::Initialize();


	// モデルを読み込む
	m_model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("Sky");

}

void Sky::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	//オブジェクトか描画が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsRenderActive())
	{
		return;
	}


	BaseEntity::Render(view, projection);



	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();


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

	BaseEntity::Render(view, projection);

	// モデルを描画する
	m_model->Draw(context, *states, BaseEntity::GetWorldMatrix(), view, projection);

}

void Sky::Update(const float& elapsedTime)
{
	//オブジェクトか更新が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}

	BaseEntity::Update(elapsedTime);

}











