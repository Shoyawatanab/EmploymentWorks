#include "pch.h"
#include "RenderManager.h"
#include "GameBase/Camera/Camera.h"
#include "GameBase/Common/Commons.h"


#include "GameBase/Camera/Camera.h"

/// <summary>
/// �R���X�g���N�^
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
{
	
	using namespace DirectX;
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// �v���~�e�B�u�o�b�`�A�x�[�V�b�N�G�t�F�N�g����������
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);
	m_basicEffect = std::make_unique<BasicEffect>(device);
	m_basicEffect->SetVertexColorEnabled(true);

	//// ���̓��C�A�E�g���쐬����
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexPositionColor>(
			device,
			m_basicEffect.get(),
			m_layout.ReleaseAndGetAddressOf()
		)
	);
	
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
RenderManager::~RenderManager()
{
	m_models.clear();
	m_colliders.clear();
	m_uis.clear();
	m_effects.clear();
	m_roundShadow.clear();
}


/// <summary>
/// �`��
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

	for (auto& ui : m_uis)
	{
		if (!ui->GetActive()) { continue; }

		ui->Render();
	}
	


	//�f�o�b�N���s���̂ݏ���
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
/// ���f���̒ǉ�
/// </summary>
/// <param name="comp"></param>
void RenderManager::AddModel(ModelComponent* comp)
{
	//���f�������邩
	auto model = std::find(m_models.begin(), m_models.end(), comp);

	//�Ȃ����
	if (model == m_models.end())
	{
		//�ǉ�
		m_models.push_back(std::move(comp));

	}


}

/// <summary>
/// ���f���̍폜
/// </summary>
/// <param name="comp"></param>
void RenderManager::RemoveModel(ModelComponent* comp)
{
	//���f�������邩
	auto model = std::find(m_models.begin(), m_models.end(),comp);
	//�����
	if (model != m_models.end())
	{
		//�폜
		m_models.erase(model);

	}


}

/// <summary>
/// UI�R���|�[�l���g�̒ǉ�
/// </summary>
/// <param name="comp">UI�R���|�[�l���g</param>
void RenderManager::AddUserInterface(ImageComponent* comp)
{
	//UI�����邩
	auto ui = std::find(m_uis.begin(), m_uis.end(), comp);

	//�Ȃ����
	if (ui == m_uis.end())
	{
		//�ǉ�
		m_uis.push_back(std::move(comp));

	}
}

/// <summary>
/// UI�R���|�[�l���g�̍폜
/// </summary>
/// <param name="comp">UI�R���|�[�l���g</param>
void RenderManager::RemoveUserInterface(ImageComponent* comp)
{
	//UI�����邩
	auto ui = std::find(m_uis.begin(), m_uis.end(), comp);
	//�����
	if (ui != m_uis.end())
	{
		//�폜
		m_uis.erase(ui);

	}
}

void RenderManager::AddCollider(ColliderComponent* comp)
{
//�f�o�b�N���s���̂ݏ���
#ifdef _DEBUG

	//���f�������邩
	auto collider = std::find(m_colliders.begin(), m_colliders.end(), comp);

	//�Ȃ����
	if (collider == m_colliders.end())
	{
		//�ǉ�
		m_colliders.push_back(comp);
	}
#endif


}

/// <summary>
/// �G�t�F�N�g�R���|�[�l���g�̒ǉ�
/// </summary>
/// <param name="comp">�R���|�[�l���g</param>
void RenderManager::AddEffect(EffectComponent* comp)
{
	//���邩������
	auto effect = std::find(m_effects.begin(), m_effects.end(), comp);

	//�Ȃ����
	if (effect == m_effects.end())
	{
		m_effects.push_back(comp);
	}


}

/// <summary>
/// �ۉe�̒ǉ�
/// </summary>
/// <param name="comp">�R���|�[�l���g</param>
void RenderManager::AddRoundShadow(RoundShadowComponent* comp)
{

	auto roundShadow = std::find(m_roundShadow.begin(), m_roundShadow.end(), comp);

	if (roundShadow == m_roundShadow.end())
	{
		m_roundShadow.push_back(comp);
	}



}


