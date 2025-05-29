/*
	�`���[�W�G�t�F�N�g�N���X
*/
#pragma once
#include "Game/Interface/IEffect.h"

// �O���錾
class ParticleUtility;


class ChargeEffect : public IEffect
{
public:
	//�R���X�^���g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
	};

	//�C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	//�����Ԋu
	static constexpr float GENERATION_INTERVAL = 0.5f;
	//��������
	static constexpr float GENERATION_TIME = 1.5f;

public:
	//�G�t�F�N�g���L�����ǂ���
	const bool& GetIsActive() override { return m_isActive; };
	//�G�t�F�N�g���L�����ǂ����̓o�^
	void SetIsActive(const bool& isActive) override {	m_isActive = isActive;};
	//���W�̓o�^
	void SetPosition(const DirectX::SimpleMath::Vector3& position) override { m_position = position; };
	//�傫���̓o�^
	void SetScale(const DirectX::SimpleMath::Vector3& scale) override { m_scale = scale; };
	//�G�t�F�N�g�̎�ނ̃^�O
	EffectType GetEffectType()  override { return EffectType::CHARGE_EFFECT; };

public:
	//�R���X�g���N�^
	ChargeEffect(CommonResources* resources);
	//�f�X�g���N�^
	~ChargeEffect() override;
	//������
	void Initialize() override;
	//�X�V����
	void Update(const float& elapsedTime) override;
	//�`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const  DirectX::SimpleMath::Matrix& proj) override;

private:
	//�G�t�F�N�g�̐���
	void Create(void* datas) override;
	//�V�F�[�_�[�̍쐬
	void CreateShader();
	//���[�e�B���e�B�̍쐬
	void CreateUtility();

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�I�u�W�F�N�g���L�����ǂ���
	bool m_isActive;
	//���W
	DirectX::SimpleMath::Vector3 m_position;
	//�傫��
	DirectX::SimpleMath::Vector3 m_scale;
	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	//	���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//	�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;
	//	�e�N�X�`���n���h��
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;
	//	���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	�s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//	�W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
	//�r���{�[�h�s��
	DirectX::SimpleMath::Matrix m_billboard;
	//���_���
	std::vector<DirectX::VertexPositionColorTexture> m_vertices;
	//���[�e�B���e�B�N���X
	std::vector<ParticleUtility> m_ChargeEffectUtility;
	//����
	float m_time;

};