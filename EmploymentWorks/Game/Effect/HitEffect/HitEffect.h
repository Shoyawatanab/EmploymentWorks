/*
	�q�b�g�G�t�F�N�g�N���X
*/
#pragma once
#include "Game/Interface/IEffect.h"

//�O���錾
class CommonResources;
class CircleParticle;

class HitEffect : public IEffect
{


public:

	//�I�u�W�F�N�g���L�����ǂ���
	bool GetIsActive() override { return m_isActive; };
	//�I�u�W�F�N�g���L�����ǂ����̓o�^
	void SetIsActive(bool isActive) override { m_isActive = isActive; };
	//�G�t�F�N�g�̎�ނ̃^�O
	EffectType GetEffectType()  override { return EffectType::HIT_EFFECT; };
	//���W�̓o�^
	void SetPosition(DirectX::SimpleMath::Vector3 position) override;
	//�傫���̓o�^
	void SetScale(DirectX::SimpleMath::Vector3 scale) override;


public:
	// �R���X�g���N�^
	HitEffect(CommonResources* resources);
	//�f�X�g���N�^
	~HitEffect() override;
	//������
	void Initialize() override;
	//�X�V����
	void Update(const float& elapsedTime) override;
	//�`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const  DirectX::SimpleMath::Matrix& proj) override;

	// �I������
	void Finalize();

private:
	//�G�t�F�N�g�̍쐬
	void Create(void* datas) override;

private:
	//���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�o�ߎ���
	float m_time;
	//�I�u�W�F�N�g���L����
	bool m_isActive;

	//�~�̃G�t�F�N�g�N���X
	std::unique_ptr<CircleParticle> m_circleHitEffect;



};

