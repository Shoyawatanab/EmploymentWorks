//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2025/1/31
// <file>			ParticleUtility.cpp
// <�T�v>			�p�[�e�B�N���̊�{�N���X
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "pch.h"
#include "Particleutility.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="life">��������</param>
/// <param name="pos">���W</param>
/// <param name="velocity">���x</param>
/// <param name="accele">�����x</param>
/// <param name="startScale">�����T�C�Y</param>
/// <param name="endScale">�ŏI�T�C�Y</param>
/// <param name="startColor">�����F</param>
/// <param name="endColor">�ŏI�F</param>
ParticleUtility::ParticleUtility(
	float life,
	DirectX::SimpleMath::Vector3 pos,
	DirectX::SimpleMath::Vector3 velocity,
	DirectX::SimpleMath::Vector3 accele,
	DirectX::SimpleMath::Vector3 startScale, DirectX::SimpleMath::Vector3 endScale,
	DirectX::SimpleMath::Quaternion startRotate, DirectX::SimpleMath::Quaternion endRotate,
	DirectX::SimpleMath::Color startColor, DirectX::SimpleMath::Color endColor)
{
	//	�^����ꂽ�������ԁis�j���擾
	m_startLife =
		m_life = life;

	//	�����ʒu���擾
	m_position = pos;
	//	�ړ��x�N�g�����擾
	m_velocity = velocity;
	//	�����x�x�N�g�����擾
	m_accele = accele;

	//	���߂̃T�C�Y���擾
	m_startScale =
		m_nowScale = startScale;
	//	�I���̃T�C�Y���擾
	m_endScale = endScale;

	m_startRotate 
		= m_nowRotate = startRotate;
	m_endRotate = endRotate;


	//	���߂̐F���擾
	m_startColor =
		m_nowColor = startColor;
	//	�I���̐F���擾
	m_endColor = endColor;

	m_addForce = DirectX::SimpleMath::Vector3::Zero;

	m_easingType = NakashiLib::Easing::EasingType::InSine;

	for (int i = 0; i < 3; i++)
	{
		m_easingSize[i] = NakashiLib::Easing::Easing();
	}
	for (int i = 0; i < 4; i++)
	{
		m_easingColor[i] = NakashiLib::Easing::Easing();
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ParticleUtility::~ParticleUtility()
{
}
/// <summary>
/// �X�V�֐�
/// </summary>
/// <returns>��������(life)������Ԃ�true</returns>
bool ParticleUtility::Update(float elapsedTime)
{
	// ���Ԍo�߂Ői�s�x
	float t = 1.0f - m_life / m_startLife;
	float speed = elapsedTime / m_startLife;

	m_nowScale.x = m_easingSize[0].Selection(m_easingType, speed, m_startScale.x, m_endScale.x);
	m_nowScale.y = m_easingSize[1].Selection(m_easingType, speed, m_startScale.y, m_endScale.y);
	m_nowScale.z = m_easingSize[2].Selection(m_easingType, speed, m_startScale.z, m_endScale.z);

	// ��]�͂��̂܂�Lerp�i�K�v�Ȃ�Easing�j
	m_nowRotate = DirectX::SimpleMath::Quaternion::Lerp(m_startRotate, m_endRotate, t);

	// Easing�ŐF�ω�
	m_nowColor.x = m_easingColor[0].Selection(m_easingType, speed, m_startColor.x, m_endColor.x);
	m_nowColor.y = m_easingColor[1].Selection(m_easingType, speed, m_startColor.y, m_endColor.y);
	m_nowColor.z = m_easingColor[2].Selection(m_easingType, speed, m_startColor.z, m_endColor.z);
	m_nowColor.w = m_easingColor[3].Selection(m_easingType, speed, m_startColor.w, m_endColor.w);

	m_velocity += m_accele * elapsedTime;
	m_velocity += m_addForce * elapsedTime;
	m_position += m_velocity * elapsedTime;
	//	���C�t�����炵�Ă���
	m_life -= elapsedTime;
	//	���C�t��0�����Ȃ玩�g�������Ă��炤
	if (m_life < 0.0f)
	{
		return false;
	}

	return true;
}

void ParticleUtility::SetEasing(NakashiLib::Easing::EasingType easingType)
{
	m_easingType = easingType;


}

