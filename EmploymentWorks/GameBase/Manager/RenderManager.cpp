/*
	クラス名     : RenderManager
	説明         : 描画マネージャー
	補足・注意点 : Sceneで宣言
*/
#include "pch.h"
#include "RenderManager.h"
#include "GameBase/Camera/Camera.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/Camera/Camera.h"



/// <summary>
/// コンストラクタ
/// </summary>
RenderManager::RenderManager()
	:
	m_models{}
	,m_colliders{}
	,m_basicEffect{}
	,m_batch{}
	,m_effects{}
	,m_layout{}
	,m_roundShadow{}
	,m_canvass{}
{
	
	using namespace DirectX;
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// プリミティブバッチ、ベーシックエフェクトを準備する
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);
	m_basicEffect = std::make_unique<BasicEffect>(device);
	m_basicEffect->SetVertexColorEnabled(true);

	//// 入力レイアウトを作成する
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexPositionColor>(
			device,
			m_basicEffect.get(),
			m_layout.ReleaseAndGetAddressOf()
		)
	);
	
}


/// <summary>
/// デストラクタ
/// </summary>
RenderManager::~RenderManager()
{
	m_models.clear();
	m_colliders.clear();
	m_canvass.clear();
	m_effects.clear();
	m_roundShadow.clear();

}


/// <summary>
/// 描画
/// </summary>
/// <param name="view"></param>
/// <param name="projection"></param>
void RenderManager::Render(const Camera& camera)
{
	for (auto& model : m_models)
	{
		if (!model->GetActive()) { continue; }
		model->Render(camera);
	}

	for (auto& shadow : m_roundShadow)
	{
		if(!shadow->GetActive()) { continue; }
		shadow->Render(camera);
	}

	for (auto& effect : m_effects)
	{
		if (!effect->GetActive()) { continue; }
		effect->Render(camera);
	}

	for (auto& canvas : m_canvass)
	{

		canvas.second->Render(camera);
	}
	


	//デバック実行時のみ処理
#ifdef _DEBUG
	for (auto& collider : m_colliders)
	{
		if (collider->GetActive())
		{
			collider->Render(camera.GetViewMatrix(), camera.GetProjectionMatrix(), m_batch.get(), m_basicEffect.get(), m_layout.Get());

		}
	}
#endif
}

/// <summary>
/// モデルの追加
/// </summary>
/// <param name="comp"></param>
void RenderManager::AddModel(ModelComponent* comp)
{
	//モデルがあるか
	auto model = std::find(m_models.begin(), m_models.end(), comp);

	//なければ
	if (model == m_models.end())
	{
		//追加
		m_models.push_back(std::move(comp));

	}


}

/// <summary>
/// モデルの削除
/// </summary>
/// <param name="comp"></param>
void RenderManager::RemoveModel(ModelComponent* comp)
{
	//モデルがあるか
	auto model = std::find(m_models.begin(), m_models.end(),comp);
	//あれば
	if (model != m_models.end())
	{
		//削除
		m_models.erase(model);

	}


}

/// <summary>
/// キャンバスの追加
/// </summary>
/// <param name="canvas">追加キャンバス</param>
void RenderManager::AddCanvas(Canvas* canvas)
{
	//キャンバスの種類の取得
	auto canvasType = canvas->GetRenderType();


	//キャンバスがあるか探す
	auto sertchCanvas = m_canvass.find(canvasType);

	//なければ
	if (sertchCanvas == m_canvass.end())
	{
		//追加
		m_canvass[canvas->GetRenderType()] = canvas;

	}


}

/// <summary>
/// キャンバスの削除
/// </summary>
/// <param name="canvas">削除キャンバス</param>
void RenderManager::RemoveCanvas(Canvas* canvas)
{
	//キャンバスの種類の取得
	auto canvasType = canvas->GetRenderType();


	//キャンバスがあるか探す
	auto sertchCanvas = m_canvass.find(canvasType);


	//あれば
	if (sertchCanvas != m_canvass.end())
	{
		//削除
		m_canvass.erase(sertchCanvas);

	}

}


void RenderManager::AddCollider(ColliderComponent* comp)
{
	UNREFERENCED_PARAMETER(comp);
//デバック実行時のみ処理
#ifdef _DEBUG

	//モデルがあるか
	auto collider = std::find(m_colliders.begin(), m_colliders.end(), comp);

	//なければ
	if (collider == m_colliders.end())
	{
		//追加
		m_colliders.push_back(comp);
	}
#endif


}

/// <summary>
/// エフェクトコンポーネントの追加
/// </summary>
/// <param name="comp">コンポーネント</param>
void RenderManager::AddEffect(EffectComponent* comp)
{
	//あるかさがす
	auto effect = std::find(m_effects.begin(), m_effects.end(), comp);

	//なければ
	if (effect == m_effects.end())
	{
		m_effects.push_back(comp);
	}


}

/// <summary>
/// 丸影の追加
/// </summary>
/// <param name="comp">コンポーネント</param>
void RenderManager::AddRoundShadow(RoundShadowComponent* comp)
{

	auto roundShadow = std::find(m_roundShadow.begin(), m_roundShadow.end(), comp);

	if (roundShadow == m_roundShadow.end())
	{
		m_roundShadow.push_back(comp);
	}



}


/// <summary>
/// キャンバスの取得
/// </summary>
/// <param name="type">取得したいキャンバスの種類</param>
/// <returns>s取得結果</returns>
Canvas* RenderManager::GetCanvas(Canvas::RenderType type)
{

	//キャンバスがあるか探す
	auto sertchCanvas = m_canvass.find(type);

	//なければ
	if (sertchCanvas == m_canvass.end())
	{
		
		return nullptr;
	}

	return m_canvass[type];
}
