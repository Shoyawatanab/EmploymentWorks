/*
* �X�e�[�ƃp�^�[���̃C���^�[�t�F�[�X
*/
#pragma once
#include "pch.h"

class CommonResources;

class IEffect
{
public:
	//�G�t�F�N�g�̎��
	enum  class EffectType
	{

		EXPLOSION
		,PLAYER_DAMAGE
		,PARTICLE
		, HIT_EFFECT
		,CHARGE_EFFECT
	};

public:
	//�f�X�g���N�^
	virtual ~IEffect() = default;
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update(const float& elapsedTime) = 0;
	//�`��
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) = 0;
	//�L�����ǂ����̎擾
	virtual const bool& GetIsActive() = 0;
	//�L�����ǂ����̓o�^
	virtual void SetIsActive(const bool& isActive) = 0;
	//�G�t�F�N�g�̎�ނ̎擾
	virtual EffectType GetEffectType() = 0;
	//���W�̓o�^
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;
	//�傫���̓o�^
	virtual void SetScale(const DirectX::SimpleMath::Vector3& scale) = 0;
	//�쐬
	virtual void Create(void* datas) = 0;
};
