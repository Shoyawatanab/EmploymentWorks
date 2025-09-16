/*
	クラス名     : Canvas
	説明         : UIキャンバスの基底クラス
	補足・注意点 :
*/
#include "pch.h"
#include "Canvas.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Manager/RenderManager.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
/// <param name="type">描画の種類</param>
Canvas::Canvas(Scene* scene, RenderType type)
	:
	Actor(scene)
	,m_type{type}
{

	//描画マネージャーにキャンバスの登録
	GetScene()->GetRenderMangaer()->AddCanvas(this);

}

/// <summary>
/// デストラクタ
/// </summary>
Canvas::~Canvas()
{

	GetScene()->GetRenderMangaer()->RemoveCanvas(this);
	m_imageComponent.clear();

}

/// <summary>
/// ImageComponentの追加
/// </summary>
/// <param name="comp">追加コンポーネント</param>
void Canvas::AddImageComponent(ImageComponent* comp)
{
	//存在しているか探す
	auto sertchComp = std::find(m_imageComponent.begin(), m_imageComponent.end(), comp);
	//ないなら
	if (sertchComp == m_imageComponent.end())
	{
		//追加
		m_imageComponent.push_back(comp);
	}


}


