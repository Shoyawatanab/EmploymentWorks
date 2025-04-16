/*
	@file	BeamChargeEffect.h
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


class BeamChargeEffect final
{

public:

	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }

	void SetPosition(DirectX::SimpleMath::Vector3 position) { m_position = position; }

	DirectX::SimpleMath::Quaternion GetRotate() { return m_initialRotate; }

	void SetRotate(DirectX::SimpleMath::Quaternion rotate) { m_initialRotate = rotate; }

	DirectX::SimpleMath::Vector3 GetScale() { return m_scale; }

	void SetScale(DirectX::SimpleMath::Vector3 scale) { m_scale = scale; }

	DirectX::SimpleMath::Vector3 GetInitialScale() { return m_initialScale; }


public:
	BeamChargeEffect();
	~BeamChargeEffect();

	void Initialize(CommonResources* resoure,DirectX::SimpleMath::Vector3 position,DirectX::SimpleMath::Quaternion rotate) ;
	void Update(float elapsedTime);
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection) ;
	void Finalize();

	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^
	void AddPointer(Beam* beam);

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
	DirectX::Model* m_model;

	DirectX::SimpleMath::Vector3 m_position;

	DirectX::SimpleMath::Vector3 m_scale;

	DirectX::SimpleMath::Quaternion m_initialRotate;


	DirectX::SimpleMath::Vector3 m_initialScale;

	//State



	Beam* m_beam;

	DirectX::SimpleMath::Vector3 m_initialPosition;


};
