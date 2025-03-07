#include "pch.h"
#include "Model3D.h"

#include "Game/CommonResources.h"
#include "DeviceResources.h"

//	���O��Ԃ̎g�p
using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
WataLib::Model3D::Model3D()
	:
	m_commonResources{},
	m_scale{}
{
}

/// <summary>
/// �J�n�֐�
/// </summary>
/// <param name="pDeviceContext">�f�o�C�X�R���e�L�X�g�̃|�C���^</param>
/// <param name="pCommonStatesm">���ʃX�e�[�g�̃|�C���^</param>
/// <param name="modelHandle">���f���n���h��</param>
void WataLib::Model3D::Initialize
(
	CommonResources* resouce, const wchar_t* szFileName, DirectX::SimpleMath::Vector3 Pos, DirectX::SimpleMath::Vector3 Scale
)
{

	m_commonResources = resouce;
	m_position = Pos;
	m_scale = Scale;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();


	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device,szFileName, *fx);


}

/// <summary>
/// �`��֐�
/// </summary>
/// <param name="camera">�J����</param>
void WataLib::Model3D::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();


	//	���[���h�s��̍쐬
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	world *= SimpleMath::Matrix::CreateScale			(m_scale);		//	�X�P�[��
	world *= SimpleMath::Matrix::CreateFromQuaternion	(m_rotate);		//	��]
	world *= SimpleMath::Matrix::CreateTranslation		(m_position);	//	���W

	m_model->Draw(context, *states, world, view, projection);

}
