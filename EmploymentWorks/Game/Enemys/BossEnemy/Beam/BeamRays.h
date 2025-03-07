/*
	@file	BeamRays.h
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


class BeamRays : public BaseEntity 
{
public:


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
	BeamRays(CommonResources* resources, BaseEntity* parent);
	
	//�f�X�g���N�^
	~BeamRays() override;

	//IObject
		//������
	void Initialize() override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//�X�V����
	void  Update(const float& elapsedTime) override;
	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^
	void AddPointer(Beam* beam);

private:
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//	���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	�s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;



	// ���f��
	std::unique_ptr<DirectX::Model> m_model;

	DirectX::SimpleMath::Quaternion m_initialRotate;


	DirectX::SimpleMath::Vector3 m_target;

	DirectX::SimpleMath::Vector3 m_initialScale;

	//State

	//�r�[���ׂ̍�
	float m_thickness;

	bool m_isHit;

	float m_maxLength;

	Beam* m_beam;

	DirectX::SimpleMath::Vector3 m_initialPosition;

};
