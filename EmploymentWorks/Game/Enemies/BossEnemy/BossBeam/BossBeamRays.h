/*
	@file	BossBeamRays.h
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


class BossBeamRays : public Actor 
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


public:


	DirectX::SimpleMath::Vector3 GetTarget() { return m_target; }
 
	void SetTarget(DirectX::SimpleMath::Vector3 target) { m_target = target; }

	DirectX::SimpleMath::Quaternion GetRotate() { return m_initialRotate; }

	void SetRotate(DirectX::SimpleMath::Quaternion rotate) { m_initialRotate = rotate; }


	DirectX::SimpleMath::Vector3 GetInitialScale() { return m_initialScale; }

public:
	//�R���X�g���N
	BossBeamRays(Scene* scene);
	
	//�f�X�g���N�^
	~BossBeamRays() override;

	
	//������
	void Initialize() override;


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
	//�����̑傫��
	DirectX::SimpleMath::Vector3 m_initialScale;
	//�r�[���ׂ̍�
	float m_thickness;
	//�����������ǂ���
	bool m_isHit;
	//�������W
	DirectX::SimpleMath::Vector3 m_initialPosition;

};
