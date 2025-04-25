/*
	@file	ChargeEffect.h
	@brief	��ʓI�ȃV�[���N���X
*/
#pragma once
#include "Game/Interface/IEffect.h"

// �O���錾
class ParticleUtility;


class ChargeEffect : public IEffect
{
public:
	//	�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
	};

	//	�֐�
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

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
	//�G�t�F�N�g���L�����ǂ���
	bool GetIsActive() override { return m_isActive; };
	//�G�t�F�N�g���L�����ǂ����̓o�^
	void SetIsActive(bool isActive) override;
	//�G�t�F�N�g�̎�ނ̃^�O
	EffectType GetEffectType()  override { return EffectType::ChargeEffect; };
	//���W�̓o�^
	void SetPosition(DirectX::SimpleMath::Vector3 position) override { m_position = position; };
	//�傫���̓o�^
	void SetScale(DirectX::SimpleMath::Vector3 scale) override { m_scale = scale; };
	//�G�t�F�N�g�̐���
	void Create(void* datas) override;
	//
	void LoadTexture(const wchar_t* path);
	//
	void CreateShader();
	//
	void CreateUtikity();

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	bool m_isActive;
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_scale;
	float m_timer;
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
	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;
	DirectX::SimpleMath::Matrix m_billboard;
	std::vector<DirectX::VertexPositionColorTexture> m_vertices;


	DirectX::SimpleMath::Vector3 m_cameraPosition;
	DirectX::SimpleMath::Vector3 m_cameraTarget;


	std::vector<ParticleUtility> m_ChargeEffectUtility;

	float m_time;

};