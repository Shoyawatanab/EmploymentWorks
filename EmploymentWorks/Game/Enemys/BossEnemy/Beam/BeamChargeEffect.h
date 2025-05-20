/*
	@file	BeamChargeEffect.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Entities/BaseEntity.h"


// �O���錾
class CommonResources;
class Beam;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BeamChargeEffect :public BaseEntity
{

public:
	//�C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//�����̑傫��
	static constexpr  DirectX::SimpleMath::Vector3 INITIALSCALE {0.1f, 0.1f, 0.1f};

public:


public:
	//�R���X�g���N
	BeamChargeEffect(CommonResources* resoure, DirectX::SimpleMath::Vector3 scale, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotate);
	//�f�X�g���N�^
	~BeamChargeEffect();
	//������
	void Initialize() override ;
	//�X�V����
	void Update(const float& elapsedTime) override ;
	//�`�揈��
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection) ;
	//
	void Finalize();

	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^
	void AddPointer(Beam* beam);

private:


	//�����ɂȂ�����
	void OnDisable() override ;

private:


	//	���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	�s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//�C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	// ���f��
	DirectX::Model* m_model;
	//�r�[��
	Beam* m_beam;
	//�������W
	DirectX::SimpleMath::Vector3 m_initialPosition;


};
