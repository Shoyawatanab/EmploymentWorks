/*
	�q�b�g�G�t�F�N�g�N���X
*/
#pragma once

#include "Game/Interface/IEffect.h"

class CommonResources;
class CircleParticle;

class HitEffect : public IEffect
{


public:


	bool GetIsActive() override { return m_isActive; };

	void SetIsActive(bool isActive) override { m_isActive = isActive; };

	EffectType GetEffectType()  override { return EffectType::HitEffect; };

	void SetPosition(DirectX::SimpleMath::Vector3 position) override;

	void SetScale(DirectX::SimpleMath::Vector3 scale) override;


public:
	// �R���X�g���N�^
	HitEffect(CommonResources* resources);
	//�f�X�g���N�^
	~HitEffect() override;
	//������
	void Initialize() override;
	//�X�V
	void Update(const float& elapsedTime) override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const  DirectX::SimpleMath::Matrix& proj) override;

	// �I������
	void Finalize();

	void Create(void* datas) override;

private:
	//���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�o�ߎ���
	float m_time;
	bool m_isActive;

	//
	std::unique_ptr<CircleParticle> m_circleHitEffect;



};

