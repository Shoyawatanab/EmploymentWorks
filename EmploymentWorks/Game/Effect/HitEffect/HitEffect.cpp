#include "pch.h"
#include "HitEffect.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/BinaryFile.h"
#include "Game/Effect/HitEffect/CircleParticle.h"
#include "Game/Observer/EventParams.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
HitEffect::HitEffect(CommonResources* resources)
	:
	m_commonResources{resources}
	,m_time{}
	,m_isActive{ false }
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
HitEffect::~HitEffect()
{

}

/// <summary>
/// ������
/// </summary>
void HitEffect::Initialize()
{

	//�O�̉~
	m_circleHitEffect = std::make_unique<CircleParticle>(m_commonResources);
	
	//������
	m_circleHitEffect->Initialize();
	m_time = 0;

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void HitEffect::Update(const float& elapsedTime)
{
	//�I�u�W�F�N�g���L����
	if (!m_isActive)
	{
		return;
	}

	//�~�̍X�V�ƏI��������ǂ���
	if (m_circleHitEffect->Update(elapsedTime))
	{
		m_isActive = false;
	}

}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void HitEffect::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//�I�u�W�F�N�g���L�����ǂ���
	if (!m_isActive)
	{
		return;
	}

	//�`��
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
/// �q�b�g�G�t�F�N�g�̍쐬
/// </summary>
/// <param name="datas">�f�[�^</param>
void HitEffect::Create(void* datas)
{

	//�f�[�^���L���X�g
	UnknownDataThree* data = static_cast<UnknownDataThree*>(datas);

	//�f�[�^������W���擾���ēo�^
	SetPosition(*static_cast<DirectX::SimpleMath::Vector3*>(data->data1));
	//�f�[�^����傫�����擾���ēo�^
	SetScale(*static_cast<DirectX::SimpleMath::Vector3*>(data->data2));
	//���Ԃ����Z�b�g
	m_circleHitEffect->SetTime(0.0f);

}

// �I������
void HitEffect::Finalize()
{
}


