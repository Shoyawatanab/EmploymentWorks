//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2025/1/31
// <file>			ParticleUtility.h
// <�T�v>			�p�[�e�B�N���̊�{�N���X
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include "GameBase/Common/Commons.h"
#include "Libraries/Easing.h"
class ParticleUtility
{
public:
	//	�֐�
	//	�R���X�g���N�^�i�����ݒ�j
	ParticleUtility(
		float life,
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Vector3 velocity,
		DirectX::SimpleMath::Vector3 accele,
		DirectX::SimpleMath::Vector3 startScale, DirectX::SimpleMath::Vector3 endScale,
		DirectX::SimpleMath::Quaternion startRotate , DirectX::SimpleMath::Quaternion endRotate,
		DirectX::SimpleMath::Color startColor, DirectX::SimpleMath::Color endColor);
	//	�f�X�g���N�^
	~ParticleUtility();

	//	�X�V
	bool Update(float elapsedtime);

	//	getter
	const DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }


	const DirectX::SimpleMath::Vector3 GetVelocity() { return m_velocity; }

	const DirectX::SimpleMath::Vector3 GetAccele() { return m_accele; }

	const DirectX::SimpleMath::Vector3 GetNowScale() { return m_nowScale; }
	const DirectX::SimpleMath::Vector3 GetStartScale() { return m_startScale; }
	const DirectX::SimpleMath::Vector3 GetEndScale() { return m_endScale; }

	const DirectX::SimpleMath::Quaternion GetNowRotate() { return m_nowRotate; }
	const DirectX::SimpleMath::Quaternion GetStartRotate() { return m_startRotate; }
	const DirectX::SimpleMath::Quaternion GetEndRotate() { return m_endRotate; }

	const float GetLife() { return m_life; }
	const float GetStartLife() { return m_startLife; }
	const DirectX::SimpleMath::Color GetNowColor() { return m_nowColor; }
	const DirectX::SimpleMath::Color GetStartColor() { return m_startColor; }
	const DirectX::SimpleMath::Color GetEndColor() { return m_endColor; }

	const DirectX::SimpleMath::Vector3 GetAddForce() { return m_addForce; }
	void SetAddForce(DirectX::SimpleMath::Vector3 addforce) { m_addForce = addforce; }

	// �C�[�W���O���Z�b�g
	void SetEasing(NakashiLib::Easing::EasingType easingType);
private:
	//	�֐�
	//	���W
	DirectX::SimpleMath::Vector3 m_position;

	// ��]
	DirectX::SimpleMath::Quaternion m_startRotate;
	DirectX::SimpleMath::Quaternion m_nowRotate;
	DirectX::SimpleMath::Quaternion m_endRotate;

	//	���x
	DirectX::SimpleMath::Vector3 m_velocity;
	//	�����x
	DirectX::SimpleMath::Vector3 m_accele;

	//	�X�P�[��
	DirectX::SimpleMath::Vector3 m_nowScale;
	DirectX::SimpleMath::Vector3 m_startScale;
	DirectX::SimpleMath::Vector3 m_endScale;

	//	��������
	float m_life;
	float m_startLife;

	//	�J���[
	DirectX::SimpleMath::Color m_nowColor;
	DirectX::SimpleMath::Color m_startColor;
	DirectX::SimpleMath::Color m_endColor;

	// �ǉ����x
	DirectX::SimpleMath::Vector3 m_addForce;

	// �C�[�W���O�̃^�C�v
	NakashiLib::Easing::EasingType m_easingType;
	// �傫���p�C�[�W���O
	NakashiLib::Easing m_easingSize[3];
	// �F�p�C�[�W���O
	NakashiLib::Easing m_easingColor[4];

};
