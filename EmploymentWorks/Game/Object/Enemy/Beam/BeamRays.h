/*
	@file	BeamRays.h
	@brief	�v���C�V�[���N���X
*/
#pragma once

// �O���錾
class CommonResources;
class Beam;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BeamRays final
{
public:

	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
	};



public:

	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }

	void SetPosition(DirectX::SimpleMath::Vector3 position) { m_position = position; }

	DirectX::SimpleMath::Vector3 GetTarget() { return m_target; }
 
	void SetTarget(DirectX::SimpleMath::Vector3 target) { m_target = target; }

	DirectX::SimpleMath::Quaternion GetRotate() { return m_initialRotate; }

	void SetRotate(DirectX::SimpleMath::Quaternion rotate) { m_initialRotate = rotate; }

	DirectX::SimpleMath::Vector3 GetScale() { return m_scale; }

	void SetScale(DirectX::SimpleMath::Vector3 scale) { m_scale = scale; }

	DirectX::SimpleMath::Vector3 GetInitialScale() { return m_initialScale; }

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//	���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	�s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;



	// ���f��
	std::unique_ptr<DirectX::Model> m_model;
	
	DirectX::SimpleMath::Vector3 m_position;

	DirectX::SimpleMath::Vector3 m_scale;

	DirectX::SimpleMath::Quaternion m_initialRotate;

	DirectX::SimpleMath::Quaternion m_rotate;
	
	DirectX::SimpleMath::Vector3 m_target;

	DirectX::SimpleMath::Vector3 m_initialScale;

	//State

	//�r�[���ׂ̍�
	float m_thickness;

	bool m_isHit;

	float m_maxLength;

	Beam* m_beam;

	DirectX::SimpleMath::Vector3 m_initialPosition;



public:
	BeamRays();
	~BeamRays();

	void Initialize() ;
	void Update(float elapsedTime);
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection) ;
	void Finalize();
public :
	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^
	void RegistrationInformation(CommonResources* resoure,Beam* beam);


};
