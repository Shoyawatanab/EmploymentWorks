#pragma once
#include "GameBase/UI/Image.h"

class Canvas;

class GameOverBackGraund : public Image
{
public:

	//�R���X�^���g�o�b�t�@)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
		DirectX::SimpleMath::Vector4	time;
	};

	//�C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


public:
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{640, 360, 0};
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE{0.1f, 0.1f, 0};
	//�A�j���[�V��������
	static constexpr float ANIMATION_TIME = 4.0f;
public:

	//�A�j���[�V�����I�����ɗL���ɂ���I�u�W�F�N�g
	void SetActor(std::vector<Actor*> actor) { m_actor = actor; }

public:
	//�R���X�g���N
	GameOverBackGraund(Canvas* canvas);
	//�f�X�g���N�^
	~GameOverBackGraund() override;

	// �P�̍X�V
	void UpdateActor(const float& deltaTime) override;

	//�A�N�e�B�u�ɂȂ������ɌĂ΂��֐�
	void OnEnable() override;

private:

	//�`��
	void CustomRender();

	//�V�F�[�_�[�쐬
	void CreateShader(ID3D11Device1* device, ID3D11DeviceContext* context);
	
	//�摜�̓ǂݍ���
	void LoadTexture();

private:
	//�摜
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	//�R���X�g�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	//	���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//	�g�p���钸�_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	�g�p����s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//	�g�p����W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
	//����
	float m_time;

	//�A�j���[�V�������I�������ɗL���ɂ���Actor
	std::vector<Actor*> m_actor;


};

