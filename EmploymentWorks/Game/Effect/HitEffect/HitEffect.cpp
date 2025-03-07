#include "pch.h"
#include "HitEffect.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/BinaryFile.h"
#include "Game/Effect/HitEffect/CircleParticle.h"
#include "Game/Observer/EventParams.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;





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


	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();



	m_time = 0;
	//�O�̉~
	m_circleHitEffect = std::make_unique<CircleParticle>(m_commonResources);

	m_circleHitEffect->Initialize();

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void HitEffect::Update(const float& elapsedTime)
{
	if (!m_isActive)
	{
		return;
	}

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

	if (!m_isActive)
	{
		return;
	}

	m_circleHitEffect->Render(view, proj);

}


void HitEffect::SetPosition(DirectX::SimpleMath::Vector3 position)
{

	m_circleHitEffect->SetPosition(position);

}

void HitEffect::SetScale(DirectX::SimpleMath::Vector3 scale)
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
	EventParams::CreateHitEffectDatas* data = static_cast<EventParams::CreateHitEffectDatas*>(datas);

	//�f�[�^������W���擾���ēo�^
	SetPosition(data->Position);
	//�f�[�^����傫�����擾���ēo�^
	SetScale(data->Scale);
	//���Ԃ����Z�b�g
	m_circleHitEffect->SetTime(0.0f);
}

// �I������
void HitEffect::Finalize()
{
}


