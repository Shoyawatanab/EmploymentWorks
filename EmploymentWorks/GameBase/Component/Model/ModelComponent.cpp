#include "pch.h"
#include "ModelComponent.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Manager/RenderManager.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/GameResources.h"
#include "GameBase/Camera/Camera.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="owner">���L��</param>
/// <param name="modelMame">���f����</param>
ModelComponent::ModelComponent(Actor* owner, std::string modelMame)
	:
	Component(owner)
{

	m_commonResources = CommonResources::GetInstance();

	//���f���̎擾
	m_model = GameResources::GetInstance()->GetModel(modelMame);

	GetActor()->GetScene()->GetRenderMangaer()->AddModel(this);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ModelComponent::~ModelComponent()
{
	//�폜
	GetActor()->GetScene()->GetRenderMangaer()->RemoveModel(this);

}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="camera">�J����</param>
void ModelComponent::Render(const Camera& camera)
{

	//���f���`��
	m_model->Draw(m_commonResources->GetDeviceResources()->GetD3DDeviceContext()
		, *m_commonResources->GetCommonStates()
		, GetActor()->GetTransform()->GetWorldMatrix()
		, camera.GetViewMatrix()
		, camera.GetProjectionMatrix());

}
