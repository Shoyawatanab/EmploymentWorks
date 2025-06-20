//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2025/06/19
// <file>			ParticleComputeShader.h
// <�T�v>		�@�@�p�[�e�B�N���`��ɂ����R���s���[�g(�e�N�X�`���Z�b�g����Ă��Ȃ��Ƃ��ɗL��)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include "GameBase/Common/Commons.h"


class ParticleComputeShader
{
public:
	// �R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
	};

	// �R���X�g���N�^�A�f�X�g���N�^
	ParticleComputeShader(DX::DeviceResources* device);
	~ParticleComputeShader();

	// �摜�v�Z������
	void CalculateImage();

	// �V�F�[�_���\�[�X�r���[�擾
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetSRV() const { return m_outputSRV; }

private:
	// �쐬����
	void Create();


private:
	// �f�o�C�X���\�[�X
	DX::DeviceResources* m_pDR;
	// �R���s���[�g�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11ComputeShader> m_computeShader;
	// �o�͗p�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_outputTexture;
	// UAV��SRV
	Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> m_outputUAV;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_outputSRV;
	// �R���X�g�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_CBuffer;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
};
