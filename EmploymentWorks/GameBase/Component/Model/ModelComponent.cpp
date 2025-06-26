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
	,m_commonResources{}
	,m_customRender{}
	,m_renderKinds{RenderKinds::NORMAL}
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

	switch (m_renderKinds)
	{
		case ModelComponent::RenderKinds::NORMAL:
			NormalRender(camera);
			break;
		case ModelComponent::RenderKinds::CUSTOM:
			CustomRender(camera);
			break;
		default:
			break;
	}

}

/// <summary>
/// �ʏ�`��
/// </summary>
/// <param name="camera">�J����</param>
void ModelComponent::NormalRender(const Camera& camera)
{
	//���f���`��
	m_model->Draw(m_commonResources->GetDeviceResources()->GetD3DDeviceContext()
		, *m_commonResources->GetCommonStates()
		, GetActor()->GetTransform()->GetWorldMatrix()
		, camera.GetViewMatrix()
		, camera.GetProjectionMatrix());
}

/// <summary>
/// �J�X�^���`��
/// </summary>
/// <param name="camera">�J����</param>
void ModelComponent::CustomRender(const Camera& camera)
{

	m_customRender(camera);

}


/// <summary>
/// �J�X�^���`��֐��̓o�^
/// </summary>
/// <param name="customRender">�֐�</param>
void ModelComponent::SetCustomRenderFunction(std::function<void(const Camera& camera)> customRender)
{
	m_customRender = customRender;
	//��Ԃ̕ύX
	m_renderKinds = RenderKinds::CUSTOM;

}



