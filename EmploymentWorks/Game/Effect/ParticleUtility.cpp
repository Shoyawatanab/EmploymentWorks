//--------------------------------------------------------------------------------------
// File: ParticleUtil.cpp
//
// �p�[�e�B�N�����[�e�B���e�B�N���X
// position�⑬�x�Ȃǃp�[�e�B�N���P�ɕK�v�ȗv�f���i�[
// �X�V���ɐ������Ԃ���W�A�傫���Ȃǂ��Čv�Z���A
// �������s������false��Ԃ��č폜�𑣂�
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Particleutility.h"
#include "GameBase/Common/Commons.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>

using namespace DirectX;

const static float ENDLESS = -100.0f;

/// <summary>
/// �R���X�g���N�^
/// �����͏����ݒ�p�̐��l
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
	float life
	, const DirectX::SimpleMath::Vector3& pos
	, const DirectX::SimpleMath::Vector3& velocity
	, const DirectX::SimpleMath::Vector3& accele
	, const DirectX::SimpleMath::Vector3& startScale
	, const DirectX::SimpleMath::Vector3& endScale
	, const DirectX::SimpleMath::Color& startColor
	, const DirectX::SimpleMath::Color& endColor)
	:
	m_position{}
	, m_velocity{}
	, m_accele{}
	, m_nowScale{}
	, m_startScale{}
	, m_endScale{}
	, m_life{}
	, m_startLife{}
	, m_nowColor{}
	, m_startColor{}
	, m_endColor{}
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


	//	���߂̐F���擾
	m_startColor =
		m_nowColor = startColor;
	//	�I���̐F���擾
	m_endColor = endColor;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ParticleUtility::~ParticleUtility()
{
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>ture ����  false�@�I�� </returns>
bool ParticleUtility::Update(const float& elapsedTime)
{

	//	�X�P�[���B���݂̐������Ԃ���A�傫����Lerp�ŎZ�o����
	m_nowScale = SimpleMath::Vector3::Lerp(m_startScale, m_endScale, 1.0f - m_life / m_startLife);
	//	�F�B���݂̐������Ԃ���A�F��Lerp�ŎZ�o����
	m_nowColor = SimpleMath::Color::Lerp(m_startColor, m_endColor, 1.0f - m_life / m_startLife);
	//	���x�̌v�Z�B�o�ߎ��ԂƉ����x���|���Z���đ������ƂŁA�����x���l�����Ĉړ����x��ω������Ă���
	m_velocity += m_accele * elapsedTime;
	//	���W�̌v�Z�B�o�ߎ��Ԃƈړ����x����A���݂̍��W���Z�o����
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


