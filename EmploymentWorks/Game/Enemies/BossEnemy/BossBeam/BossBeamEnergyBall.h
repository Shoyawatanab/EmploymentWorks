/*
	@file	BossBeamEnergyBall.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "GameBase/Actor.h"

// �O���錾
class CommonResources;
class Beam;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}

namespace WataLib
{
	class Bounding;

}

class BossBeamEnergyBall : public Actor
{
public:

	//�R���X�^���g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4    Color;

	};

	static constexpr DirectX::SimpleMath::Vector3 INITALPOSITION { 100, 100, 0 };


public:
	//�R���X�g���N
	BossBeamEnergyBall(Scene* scene);
	
	//�f�X�g���N�^
	~BossBeamEnergyBall() override;

	
	//������
	void Initialize() override;




	//���Z�b�g
	void ReSet();

private:

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

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
	//������]
	DirectX::SimpleMath::Quaternion m_initialRotate;
	//�^�[�Q�b�g
	DirectX::SimpleMath::Vector3 m_target;
	//�����T�C�Y
	DirectX::SimpleMath::Vector3 m_initialScale;
	//�ő�T�C�Y
	DirectX::SimpleMath::Vector3 m_maxScale;
	//�ő�T�C�Y�ɂȂ鎞��
	float m_maxSizeTime;
	//����
	float m_time;




};
