//--------------------------------------------------------------------------------------
// File: UserInterface.h
//
// ���[�U�[�C���^�[�t�F�[�X�N���X
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

	//UI�̃A���J�[�|�C���g�̗񋓐�
	enum ANCHOR
	{
		TOP_LEFT = 0,
		TOP_CENTER,
		TOP_RIGHT,

		MIDDLE_LEFT,
		MIDDLE_CENTER,
		MIDDLE_RIGHT,

		BOTTOM_LEFT,
		BOTTOM_CENTER,
		BOTTOM_RIGHT

	};

	class UserInterface
	{
	public:
		//�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
		struct ConstBuffer
		{
			DirectX::SimpleMath::Vector4	windowSize;
		};
//�ϐ�
	private:
		DX::DeviceResources* m_pDR;

		Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;

		DX::StepTimer                           m_timer;
		// ���̓��C�A�E�g
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

		// �v���~�e�B�u�o�b�`
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
		//�R�����X�e�[�g
		std::unique_ptr<DirectX::CommonStates> m_states;
		// �e�N�X�`���n���h��
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
		Microsoft::WRL::ComPtr<ID3D11Resource> m_res;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_yoshiTexture;
		Microsoft::WRL::ComPtr<ID3D11Resource> m_yoshiRes;
		// ���_�V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
		// �s�N�Z���V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
		// �W�I���g���V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

		int m_windowWidth , m_windowHeight;
		int m_textureWidth, m_textureHeight;
		int m_yoshiTextureWidth, m_yoshiTextureHeight;

		DirectX::SimpleMath::Vector2 m_scale;
		DirectX::SimpleMath::Vector2 m_position;

		ANCHOR m_anchor;

//�֐�
	public:
		static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

		UserInterface();
		~UserInterface();

		void LoadTexture(const wchar_t* path);
		
		void Create(DX::DeviceResources* pDR
			, const wchar_t* path
			, DirectX::SimpleMath::Vector2 position
			,DirectX::SimpleMath::Vector2 scale
			,ANCHOR anchor);

		void Render();

		void SetWindowSize(const int &width,const int& height);

		void SetScale(DirectX::SimpleMath::Vector2 scale);
		DirectX::SimpleMath::Vector2 GetScale() { return m_scale; }
		void SetPosition(DirectX::SimpleMath::Vector2 position);
		DirectX::SimpleMath::Vector2 GetPosition() { return m_position;}
		void SetAnchor(ANCHOR anchor);
		ANCHOR GetAnchor() { return m_anchor; }


	private:

		void CreateShader();
	};