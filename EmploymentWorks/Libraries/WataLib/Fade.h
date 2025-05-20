//--------------------------------------------------------------------------------------
//	File: Fade.h
//
//	�p�[�e�B�N���N���X
//	���g���̏ꍇ��Position���̂�
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

class Fade
{
public:

	//�t�F�[�h���
	enum FadeState
	{
		NONE,
		FADE_IN,
		FADE_OUT
	};


	//�R���X�^���g�o�b�t�@)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
		DirectX::SimpleMath::Vector4	time;
	};

public:
	//	�֐�
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


public:

	//�t�F�[�h��Ԃ̓o�^
	void SetFadeState(FadeState state) { m_fadeState = state; }
	//�t�F�[�h��Ԃ̎擾
	FadeState GetFadeState() { return m_fadeState; }
	//�V�[���؂�ւ������邩�̓o�^
	void SetIsSceneChange(bool is) { m_isSceneChange = is; }
	//�V�[���؂�ւ������邩�ǂ������擾
	bool GetIsSceneChange() { return m_isSceneChange; }


public:
	//�R���X�g���N�^
	Fade(ID3D11Device1* m_device,ID3D11DeviceContext* m_contect);
	//�f�X�g���N�^
	~Fade();
	//����������
	void Initialize();
	//�X�V����
	void Update(float elapsdTime);
	//�`�揈��
	void Render();

	//�ʏ�t�F�[�h�C���̃X�^�[�g�֐�
	void StartNormalFadeIn();
	//�ʏ�t�F�[�h�A�E�g�̃X�^�[�g�֐�
	void StartNormalFadeOut();

private:
	//�V�F�[�_�[�̍쐬
	void CreateShader();

private:
	//�R���X�g�o�b�t�@
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
	//	�g�p���钸�_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_currentVS;
	//	�g�p����s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_currentPS;
	//	�g�p����W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_currentGS;
	//����
	float m_time;
	//�t�F�[�h�̎��
	FadeState m_fadeState;

	//�V�[���؂�ւ������邩
	bool m_isSceneChange;
	//�f�o�C�X
	ID3D11Device1* m_device;
	//�R���e�L�X�g
	ID3D11DeviceContext* m_context;

	//	�ʏ�t�F�[�h�C���s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_normalFadeInPS;
	//	�ʏ�t�F�[�h�A�E�g�s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_normalFadeOutPS;

	//�t�F�[�h����
	float m_maxFadeTime;

};


/*
	�@FadeIn�͊e�V�[����GetNextSceneID�֐����ŃX�^�[�g������
	FadeOut�͊e�V�[����Initialize�֐��ŃX�^�[�g������
	
*/
