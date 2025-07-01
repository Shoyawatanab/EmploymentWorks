#pragma once
#include "GameBase/Actor.h"

class Camera;
class ParticleUtility;


class Particle : public Actor
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


public:
	//�C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	//�����Ԋu
	static constexpr float GENERATION_INTERVAL = 0.5f;
	//��������
	static constexpr float GENERATION_TIME = 1.5f;
	//���[�e�B���e�B�̐�
	static constexpr int UTILITY_COUNT = 20;
	//�������a
	static constexpr float GENERATE_RADIUS = 3.0f;



public:
	//�R���X�g���N
	Particle(Scene* scene);
	//�f�X�g���N�^
	~Particle() override;

	// �R���|�[�l���g�S�̂̍X�V
	void UpdateActor(const float& deltaTime) override;

	//�`�揈��
	void Render(const Camera& camera);

	//�A�N�e�B�u�ɂȂ������ɌĂ΂��֐�
	void OnEnable() override;

	//�G�t�F�N�g�̍쐬
	void Create();

private:

	//�V�F�[�_�[�̍쐬
	void CreateShader();
	//���[�e�B���e�B�̍쐬
	void CreateUtility();


private:
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
	//���[�e�B���e�B�N���X
	std::vector<ParticleUtility> m_particleUtility;



};
