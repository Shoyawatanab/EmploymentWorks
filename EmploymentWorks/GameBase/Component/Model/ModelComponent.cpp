#include "pch.h"
#include "ModelComponent.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Manager/RenderManager.h"
#include "Libraries/WataLib/GameResources.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "GameBase/Camera/Camera.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="owner">所有者</param>
/// <param name="modelMame">モデル名</param>
ModelComponent::ModelComponent(Actor* owner, std::string modelMame)
	:
	Component(owner)
{

	m_commonResources = CommonResources::GetInstance();

	//モデルの取得
	m_model = m_commonResources->GetInstance()->GetGameResources()->GetModel(modelMame);

	GetActor()->GetScene()->GetRenderMangaer()->AddModel(this);

}

/// <summary>
/// デストラクタ
/// </summary>
ModelComponent::~ModelComponent()
{
	//削除
	GetActor()->GetScene()->GetRenderMangaer()->RemoveModel(this);

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="camera">カメラ</param>
void ModelComponent::Render(const Camera& camera)
{

	//モデル描画
	m_model->Draw(m_commonResources->GetDeviceResources()->GetD3DDeviceContext()
		, *m_commonResources->GetCommonStates()
		, GetActor()->GetTransform()->GetWorldMatrix()
		, camera.GetViewMatrix()
		, camera.GetProjectionMatrix());

}
