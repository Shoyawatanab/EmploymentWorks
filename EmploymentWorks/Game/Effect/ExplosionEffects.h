/*
	@file	ExplosionEffects.h
	@brief	��ʓI�ȃV�[���N���X
*/
#pragma once
#include "Game/Interface/IEffect.h"

// �O���錾
class CommonResources;


class ExplosionEffects : public IEffect
{
private:

	static constexpr DirectX::SimpleMath::Vector2 SCALE {2, 2};

	// �A�j���[�V�����T�C�Y
	static constexpr float ANIMATION_SIZE = 1.0f / 7.0f;	// 7��
	// �A�j���[�V�����̃C���^�[�o���F�t���[���P��
	static constexpr int ANIMATION_INTERVAL = 5;


public:


	bool GetIsActive() override { return m_isActive; };

	void SetIsActive(bool isActive) override { m_isActive = isActive; };

	EffectType GetEffectType()  override { return EffectType::Explosion; };


	void SetPosition(DirectX::SimpleMath::Vector3 position) override { m_position = position; };

	void SetScale(DirectX::SimpleMath::Vector3 scale) override { m_scale = scale; };




//�p���֌W
public:
	ExplosionEffects(CommonResources* resources);

	~ExplosionEffects() override;

	void Initialize() override;
	void Update(const float& elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& view, const  DirectX::SimpleMath::Matrix& proj) override;


	void Create(void* datas) override ;

private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	bool m_isActive;
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_scale;

	// �|���S���`��p
	// �|���S��
	DirectX::VertexPositionTexture m_vertices[4];
	// �x�[�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	// �C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_primitiveBatch;
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// �r���{�[�h�s��
	DirectX::SimpleMath::Matrix m_billboardMat;

	// �t���[���J�E���^
	int m_frameCounter;
	// �A�j���[�V�����L�[
	int m_animationKey;



};
