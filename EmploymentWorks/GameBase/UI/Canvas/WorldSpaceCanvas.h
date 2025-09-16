/*
	�N���X��     : WorldSpaceCanvas
	����         : 3D��ԗp��UI�pCanvas
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/UI/Canvas/Canvas.h"

class Camera;

class WorldSpaceCanvas : public Canvas
{
public:

	//�C���v�b�g���C�A�E�g	
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


	//�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;		DirectX::SimpleMath::Vector4    Position;				//���W
		DirectX::SimpleMath::Vector4	Size;					//�傫��
		DirectX::SimpleMath::Vector4    Rotate;                 //��]
		DirectX::SimpleMath::Vector4    Color;					//�F
		DirectX::SimpleMath::Vector4    CutRange;				//�؂���͈�
		DirectX::SimpleMath::Vector4    ViewRange;              //�\���͈�
		DirectX::SimpleMath::Vector4    FillAmount;				//�h��Ԃ���  x ���@y �c
	};

public:

	// ���_�V�F�[�_�̎擾
	Microsoft::WRL::ComPtr<ID3D11VertexShader> GetVertexShader() { return m_vertexShader; }
	// �s�N�Z���V�F�[�_�̎擾
	Microsoft::WRL::ComPtr<ID3D11PixelShader> GetPixelShader() { return m_pixelShader; }
	// �W�I���g���V�F�[�_�̎擾
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> GetGeometryShader() { return m_geometryShader; }

	//�r���{�[�h�����̃Z�b�g
	void SetIsBillboard(bool isBillboard) { m_isBillboard = isBillboard; }

public:
	//�R���X�g���N�^
	WorldSpaceCanvas(Scene* scene);
	//�f�X�g���N�^
	~WorldSpaceCanvas();

	//�`��
	void Render(const Camera& camera) override;

private:

	//�ʏ�`��
	void NormalRender(const Camera& camera,ImageComponent* comp);

private:

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_batch;
	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;


	bool m_isBillboard;


};





