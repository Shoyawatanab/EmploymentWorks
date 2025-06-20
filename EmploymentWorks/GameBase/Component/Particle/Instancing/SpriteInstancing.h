//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2025/06/16
// <file>			SpriteInstancing.h
// <�T�v>		�@�@�X�v���C�g�ł̃C���X�^���V���O
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"GameBase/Manager/ShaderManager2.h"

class SpriteInstancing
{
public:
	static const int MAX_INSTANCE = 100000;

	// �萔�o�b�t�@�\����
	struct SpriteConstantBuffer
	{
		DirectX::SimpleMath::Matrix view;
		DirectX::SimpleMath::Matrix projection;
		DirectX::SimpleMath::Vector4 CameraUp;
		DirectX::SimpleMath::Vector4 CameraRight;
		DirectX::SimpleMath::Vector4 color;
		bool onBillboard;
		DirectX::SimpleMath::Vector3 dammy;
		SpriteConstantBuffer()
		{
			memset(this, 0, sizeof(SpriteConstantBuffer));
		}
	};

	// �C���X�^���X�p�f�[�^�\����
	struct SpriteInstanceData
	{
		DirectX::SimpleMath::Vector3 position;
		DirectX::SimpleMath::Vector3 size;
		DirectX::SimpleMath::Vector4 color;
		DirectX::SimpleMath::Vector4 texCoord;
		DirectX::SimpleMath::Quaternion rotation;

		SpriteInstanceData()
		{
			position = DirectX::SimpleMath::Vector3::Zero;
			size = DirectX::SimpleMath::Vector3::One;
			color = DirectX::SimpleMath::Vector4::One;
			texCoord = DirectX::SimpleMath::Vector4(0.0f, 0.0f, 1.0f, 1.0f);
			rotation = DirectX::SimpleMath::Quaternion::Identity;
		}
	};

	// �x�[�X���_�\����
	struct BaseVertex
	{
		DirectX::SimpleMath::Vector3 position;
		DirectX::SimpleMath::Vector2 texCoord;
	};

public:
	// �R���X�g���N�^�A�f�X�g���N�^
	SpriteInstancing();
	~SpriteInstancing() = default;
	// ������
	void Initialize(ID3D11Device* device, int maxInstance = MAX_INSTANCE);
	// �e�N�X�`���ǂݍ���
	void SetTexture(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture) { m_texture = texture; }
	// �r���{�[�h����
	void SetBillboard(bool value) { m_onBillboard = value; }

	// �`��
	void Render(ID3D11DeviceContext* context,
		DirectX::DX11::CommonStates* states,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection,
		std::vector<SpriteInstanceData>& instances);
private:
	// ���_�o�b�t�@�쐬
	void CreateVertexBuffer(ID3D11Device* device);
	// �C���X�^���X�o�b�t�@�쐬
	void CreateInstanceBuffer(ID3D11Device* device);
	// �J�����̉E�E��x�N�g���v�Z
	void CalculateCameraVectors(const DirectX::SimpleMath::Matrix& view,
		DirectX::SimpleMath::Vector3& right, DirectX::SimpleMath::Vector3& up);
private:
	// ���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	// �C���X�^���X�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_instanceBuffer;
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// �V�F�[�_�Z�b�g
	ShaderSet m_shaderSet;
	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	// �C���X�^���X��
	int m_maxInstance;

	// �r���{�[�h�̗L�� true == ���� false == �Ȃ�
	bool m_onBillboard;
};
