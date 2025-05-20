/*
	@file	DamageVignette.h
	@brief	��ʓI�ȃV�[���N���X
*/
#pragma once
#include "Game/Interface/IEffect.h"



class DamageVignette : public IEffect
{
public:

	static constexpr DirectX::SimpleMath::Vector2 SCALE {2, 2};

	//	�֐�
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


	//�R���X�^���g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
		DirectX::SimpleMath::Vector4	Time;
	};

public:
	//�I�u�W�F�N�g���L����
	bool GetIsActive() override { return m_isActive; };
	//�I�u�W�F�N�g���L�����̓o�^
	void SetIsActive(bool isActive) override;
	//���W�̓o�^
	void SetPosition(DirectX::SimpleMath::Vector3 position) override { m_position = position; };
	//�傫���̓o�^
	void SetScale(DirectX::SimpleMath::Vector3 scale) override { m_scale = scale; };
	//�G�t�F�N�g�̎�ނ̃^�O
	EffectType GetEffectType()  override { return EffectType::PLAYER_DAMAGE; };


public:
	//�R���X�g���N�^
	DamageVignette(CommonResources* resources);
	//�f�X�g���N�^
	~DamageVignette() override;
	//������
	void Initialize() override;
	//�X�V����
	void Update(const float& elapsedTime) override;
	//�`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const  DirectX::SimpleMath::Matrix& proj) override;
	//
	void Finalize();

private:
	//�G�t�F�N�g�̍쐬
	void Create(void* datas) override;

private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//���W
	DirectX::SimpleMath::Vector3 m_position;
	//�傫��
	DirectX::SimpleMath::Vector3 m_scale;
	//�I�u�W�F�N�g���L����
	bool m_isActive;
	//�����x
	float m_alpha;
	//�_���[�W
	int m_damageCount;

	//�R���X�g�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	//	���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//	�g�p���钸�_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vs;
	//	�g�p����s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_ps;
	//	�g�p����W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_gs;




};
