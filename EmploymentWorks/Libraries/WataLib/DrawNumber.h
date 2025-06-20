//--------------------------------------------------------------------------------------
// File: DrawNumber.h
//
// ���[�U�[�C���^�[�t�F�[�X�N���X
//
//-------------------------------------------------------------------------------------

#pragma once

#include "GameBase/Common/Commons.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>



class DrawNumber
{
public:

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


public:
	//�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4	windowSize;
		DirectX::SimpleMath::Vector4	Diffuse;
	};

public:

	void SetScale(const DirectX::SimpleMath::Vector2& scale);
	const DirectX::SimpleMath::Vector2& GetScale() { return m_scale; }

	const DirectX::SimpleMath::Vector2& GetInialScale() { return m_initialScale; }

	void SetPosition(const DirectX::SimpleMath::Vector2& position);
	const DirectX::SimpleMath::Vector2& GetPosition() { return m_position; }

	const DirectX::SimpleMath::Vector2& GetInitialPosition() { return m_initialPosition; }

	void SetRenderRatio(const float& ratio);
	float GetRenderRatio() const { return m_renderRatio; }

	void SetRenderRatioOffset(const float& offset) { m_renderRatioOffset = offset; };
	float GetRenderRatioOffset() const { return m_renderRatioOffset; }

	void SetAlphaValue(const float& value) { m_alphaValue = value; }
	float GetAlphaValue() const { return m_alphaValue; }

	void SetIsActive(const bool& isActive) { m_isActive = isActive; }

	bool GetIsActive() const { return m_isActive; }

	int GetWidth() const { return m_textureWidth; }
	int GetHeight() const { return m_textureHeight; }


	void SetOffSetPosition(const DirectX::SimpleMath::Vector2& offsetPostion) { m_offsetPosition = offsetPostion; }

	//�֐�
public:
	//�R���X�g���N
	DrawNumber();
	//�f�X�g���N�^
	~DrawNumber();
	//�摜�̓ǂݍ���
	void LoadTexture(const wchar_t* path);
	//����
	void Create(DX::DeviceResources* pDR
		, const wchar_t* path
		, const DirectX::SimpleMath::Vector2& position
		, const DirectX::SimpleMath::Vector2& scale
		);
	//�`��
	void Render(const int& number , const DirectX::SimpleMath::Vector2& offsetPosition);


private:
	//�V�F�[�_�[�̍쐬
	void CreateUIShader();



	//�ϐ�
private:
	DX::DeviceResources* m_pDR;
	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;
	// �e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	Microsoft::WRL::ComPtr<ID3D11Resource> m_res;
	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
	//�摜�T�C�Y
	int m_textureWidth, m_textureHeight;
	//�傫��
	DirectX::SimpleMath::Vector2 m_scale;
	//���W
	DirectX::SimpleMath::Vector2 m_position;
	//�������W
	DirectX::SimpleMath::Vector2 m_initialPosition;
	//�����̑傫��
	DirectX::SimpleMath::Vector2 m_initialScale;

	float m_renderRatio;
	//
	float m_renderRatioOffset;

	//�摜�S�̂̓����x
	float m_alphaValue;

	bool m_isActive;

	DirectX::SimpleMath::Vector2 m_offsetPosition;

};
