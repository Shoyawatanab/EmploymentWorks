//--------------------------------------------------------------------------------------
// File: Particle.h
//
// �p�[�e�B�N���N���X
// ���g���̏ꍇ��Position���̂�
//
//-------------------------------------------------------------------------------------

#pragma once

#include "StepTimer.h"
#include <DeviceResources.h>
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>
#include <list>
#include "Game/Interface/IEffect.h"

//�O���錾
class CommonResources;
class ParticleUtility;



class Particle : public IEffect
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

	//	�֐�
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//���[�e�B���e�B�̐�
	static constexpr int UTILITY_COUNT = 20;
	//�������a
	static constexpr float GENERATE_RADIUS = 3.0f;

public:
	//�G�t�F�N�g���L�����ǂ���
	const bool& GetIsActive() override { return m_isActive; };
	//�G�t�F�N�g���L�����ǂ����̓o�^
	void SetIsActive(const bool& isActive) override;
	//���W�̓o�^
	void SetPosition(const DirectX::SimpleMath::Vector3& position) override { m_position = position; };
	//�傫���̓o�^
	void SetScale(const DirectX::SimpleMath::Vector3& scale) override { m_scale = scale; };
	//�G�t�F�N�g�̎�ނ̃^�O
	EffectType GetEffectType()  override { return EffectType::PARTICLE; };

public:
	//�R���X�g���N�^
	Particle(CommonResources* resources);
	//�f�X�g���N�^
	~Particle() override;
	//������
	void Initialize() override;
	//�X�V����
	void Update(const float& elapsedTime) override;
	//�`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const  DirectX::SimpleMath::Matrix& proj) override;

private:

	//�G�t�F�N�g�̍쐬
	void Create(void* datas) override;
	//�V�F�[�_�[�̍쐬
	void CreateShader();

	//�r���{�[�h�̍쐬
	void CreateBillboard(
		DirectX::SimpleMath::Vector3 target,
		DirectX::SimpleMath::Vector3 eye,
		DirectX::SimpleMath::Vector3 up);

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�I�u�W�F�N�g���L����
	bool m_isActive;
	//���W
	DirectX::SimpleMath::Vector3 m_position;
	//�傫��
	DirectX::SimpleMath::Vector3 m_scale;
	//
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;


	//	���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//	�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;
	//	�e�N�X�`���n���h��
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;
	//	�e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture2;
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
	std::vector<ParticleUtility> m_particleUtility;



};
