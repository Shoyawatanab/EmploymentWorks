/*
	�q�b�g�G�t�F�N�g�̉~�̃p�[�e�B�N��
*/
#pragma once
//�O���錾
class CommonResources;


class CircleParticle 
{
public:

	/// �R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4    diffuse;
		DirectX::SimpleMath::Vector4    time;
		

	};

	//���쎞��
	static constexpr float OPERATION_TIME = 2.0f;

public:
	//���W�̓o�^
	void SetPosition(DirectX::SimpleMath::Vector3 pos) { m_position = pos; }
	//�傫���̓o�^
	void SetScale(DirectX::SimpleMath::Vector3 scale) { m_scale = scale; }
	//���Ԃ̓o�^
	void SetTime(float time) { m_time = time; }


public:

	//�R���X�g���N�^
	CircleParticle(CommonResources* resourece);
	//�f�X�g���N�^
	~CircleParticle();
	// ������
	void Initialize();
	// �X�V����
	bool Update(float elapsedTime);
	// �`�揈��
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// �I������
	void Finalize();



private:

	//���ʃ��\�[�X
	CommonResources* m_commonResources;

	//���W
	DirectX::SimpleMath::Vector3 m_position;
	//�傫��
	DirectX::SimpleMath::Vector3 m_scale;
	//���[���h�s��
	DirectX::SimpleMath::Matrix m_world;
	//�����x
	float m_alpha;

	//�v���~�e�B�u�`��p�̃o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_Batch;
	//���_���C�A�E�g�̒�`
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	//�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	//	���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	�s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//���_���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;

	//�o�ߎ���
	float m_time;

};

