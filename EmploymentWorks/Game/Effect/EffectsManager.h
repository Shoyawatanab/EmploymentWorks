#pragma once
/*
	@file	EffectsManager.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"
#include "Game/Interface/IEffect.h"
#include "Game/Interface/IObserver.h"

// �O���錾
class CommonResources;

class EffectsManager : public IObserver<GameMessageType>
{
public:

	//�����G�t�F�N�g�̐�
	static constexpr int EXPLOION_EFFECT_COUNT = 10;
	//�p�[�e�B�N���G�t�F�N�g�̐�
	static constexpr int PARTICLE_EFFECT_COUNT = 2;
	//�q�b�g�G�t�F�N�g�̐�
	static constexpr int HIT_EFFECT_COUNT = 30;
public:
	//�R���X�g���N�^
	EffectsManager();
	//�f�X�g���N�^
	~EffectsManager() ;
	//������
	void Initialize(CommonResources* resources);
	//�X�V����
	void Update(const float& elapsedTime);
	//�`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) ;
	//
	void Finalize() ;

private:
	//�����G�t�F�N�g�̐���
	void CreateExploion(void* datas);
	//�v���C���_���[�W�G�G�t�F�N�g�̐���
	void CreatePlayerDamageEffect(void* datas);
	//�p�[�e�B�N���G�t�F�N�g�̐���
	void CreateParticle(void* datas);
	//�q�b�g�G�t�F�N�g�̐���
	void CreateHitEffect(void* datas);
	//�`���[�W�G�t�F�N�g�̐���
	void CreateChargeEffect(void* datas);
	//�ʒm
	void Notify(const Telegram<GameMessageType>& telegram)  override;
	//�G�t�F�N�g�̍쐬
	void CreateEffect();

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�G�t�F�N�g���܂Ƃ߂�ϐ�
	std::vector<std::unique_ptr<IEffect>> m_effects;



};
