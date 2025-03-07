/*
	@file	DamageVignette.h
	@brief	��ʓI�ȃV�[���N���X
*/
#pragma once
#include "Game/Interface/IEffect.h"

// �O���錾

class DamageVignette : public IEffect
{
public:

	static constexpr DirectX::SimpleMath::Vector2 SCALE {2, 2};

	//	�֐�
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


	//	�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
		DirectX::SimpleMath::Vector4	Time;
	};

public:

	bool GetIsActive() override { return m_isActive; };

	void SetIsActive(bool isActive) override;

	EffectType GetEffectType()  override { return EffectType::PlayerDamage; };


	void SetPosition(DirectX::SimpleMath::Vector3 position) override { m_position = position; };

	void SetScale(DirectX::SimpleMath::Vector3 scale) override { m_scale = scale; };


public:
	DamageVignette(CommonResources* resources);

	~DamageVignette() override;

	void Initialize() override;
	void Update(const float& elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& view, const  DirectX::SimpleMath::Matrix& proj) override;

	void Finalize();


	void Create(void* datas) override;

private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_scale;
	bool m_isActive;
	float m_alpha;
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
	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;



};
