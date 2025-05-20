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



/// <summary>
/// コンストラク
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
Sky::Sky(CommonResources* resources
	, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation)
	:
	m_model{}
	, BaseEntity(resources,scale,position,rotation)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Sky::~Sky()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
void Sky::Initialize()
{

	BaseEntity::Initialize();


	// モデルを読み込む
	m_model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("Sky");

}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void Sky::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	using namespace DirectX;

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

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Sky::Update(const float& elapsedTime)
{
	//オブジェクトか更新が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}

	BaseEntity::Update(elapsedTime);

}











