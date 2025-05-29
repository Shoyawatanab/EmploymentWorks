#include "pch.h"
#include "HitEffect.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/BinaryFile.h"
#include "Game/Effect/HitEffect/CircleParticle.h"
#include "Game/Observer/EventParams.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
HitEffect::HitEffect(CommonResources* resources)
	:
	m_commonResources{resources}
	,m_time{}
	,m_isActive{ false }
{

}

/// <summary>
/// デストラクタ
/// </summary>
HitEffect::~HitEffect()
{

}

/// <summary>
/// 初期化
/// </summary>
void HitEffect::Initialize()
{

	//外の円
	m_circleHitEffect = std::make_unique<CircleParticle>(m_commonResources);
	
	//初期化
	m_circleHitEffect->Initialize();
	m_time = 0;

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void HitEffect::Update(const float& elapsedTime)
{
	//オブジェクトが有効か
	if (!m_isActive)
	{
		return;
	}

	//円の更新と終わったかどうか
	if (m_circleHitEffect->Update(elapsedTime))
	{
		m_isActive = false;
	}

}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void HitEffect::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//オブジェクトが有効かどうか
	if (!m_isActive)
	{
		return;
	}

	//描画
	m_circleHitEffect->Render(view, proj);

}


void HitEffect::SetPosition(const DirectX::SimpleMath::Vector3& position)
{

	m_circleHitEffect->SetPosition(position);

}

void HitEffect::SetScale(const DirectX::SimpleMath::Vector3& scale)
{
	m_circleHitEffect->SetScale(scale);
}

/// <summary>
/// ヒットエフェクトの作成
/// </summary>
/// <param name="datas">データ</param>
void HitEffect::Create(void* datas)
{

	//データをキャスト
	UnknownDataThree* data = static_cast<UnknownDataThree*>(datas);

	//データから座標を取得して登録
	SetPosition(*static_cast<DirectX::SimpleMath::Vector3*>(data->data1));
	//データから大きさを取得して登録
	SetScale(*static_cast<DirectX::SimpleMath::Vector3*>(data->data2));
	//時間をリセット
	m_circleHitEffect->SetTime(0.0f);

}

// 終了処理
void HitEffect::Finalize()
{
}


