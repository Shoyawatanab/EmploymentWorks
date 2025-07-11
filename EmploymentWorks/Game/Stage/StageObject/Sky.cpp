/*
	�N���X��     : Sky
	����         : �V��
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "Sky.h"
#include "Game/Component/Components.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/Camera/Camera.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
Sky::Sky(Scene* scene)
	:
	Actor(scene)
{

	//���f���R���|�[�l���g�̒ǉ�
	m_modelComponent =  AddComponent<ModelComponent>(this, "Sky");

	m_modelComponent->SetCustomRenderFunction(std::bind(&Sky::Render, this,std::placeholders::_1));



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Sky::~Sky()
{
	// do nothing.
}

/// <summary>
/// �`��
/// </summary>
/// <param name="camera">�J����</param>
void Sky::Render(const Camera& camera)
{

	using namespace DirectX::SimpleMath;
	using namespace DirectX;

	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = CommonResources::GetInstance()->GetCommonStates();

	auto model = m_modelComponent->GetModel();

	// ���f���̃G�t�F�N�g�����X�V����
	model->UpdateEffects([](DirectX::IEffect* effect)
		{
			// �x�[�V�b�N�G�t�F�N�g��ݒ肷��
			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				// �ʂ̃��C�g�����ׂĖ���������
				basicEffect->SetLightEnabled(0, false);
				basicEffect->SetLightEnabled(1, false);
				basicEffect->SetLightEnabled(2, false);

				// ����������������
				basicEffect->SetAmbientLightColor(Colors::Black);

				// ���f����������������
				basicEffect->SetEmissiveColor(Colors::White);
			}
		}
	);

	// ���[���h�s����X�V����
	Matrix world = Matrix::Identity;

	// ���f����`�悷��
	model->Draw(context, *states, world, camera.GetViewMatrix(), camera.GetProjectionMatrix());

}













