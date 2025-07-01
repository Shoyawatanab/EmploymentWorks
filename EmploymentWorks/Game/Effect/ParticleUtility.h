#pragma once


class ParticleUtility
{
public:
	//	���W�̎擾
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }
	//�X�P�[���̎擾
	const DirectX::SimpleMath::Vector3& GetNowScale() { return m_nowScale; }
	//�F�̎擾
	const DirectX::SimpleMath::Color& GetNowColor() { return m_nowColor; }

public:
	//	�֐�
	//	�R���X�g���N�^�i�����ݒ�j
	ParticleUtility(
		float life,
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& velocity,
		const DirectX::SimpleMath::Vector3& accele,
		const DirectX::SimpleMath::Vector3& startScale,
		const DirectX::SimpleMath::Vector3& endScale,
		const DirectX::SimpleMath::Color& startColor
		, const DirectX::SimpleMath::Color& endColor);
	//	�f�X�g���N�^
	~ParticleUtility();

	//	�X�V
	bool Update(const float& elapsedTime);


private:
	//	�֐�
	//	���W
	DirectX::SimpleMath::Vector3 m_position;

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

};

