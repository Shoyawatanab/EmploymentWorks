 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto
// <����J�n��>		2025/06/16
// <file>			ShaderManager.h
// <�T�v>			�V�F�[�_�֘A�̐����}�l�[�W���[
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include"Libraries/Microsoft/ReadData.h"

/// <summary>
/// �V�F�[�_�̃^�C�v����
/// </summary>
enum class ShaderType
{
	VertexShader,
	PixelShader,
	GeometryShader
};

/// <summary>
/// �V�F�[�_�g�p�̃Z�b�g
/// </summary>
struct ShaderSet
{
	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> CBuffer;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
};

class ShaderManager2
{
public:
	/// <summary>
	/// ���_�V�F�[�_�쐬
	/// </summary>
	static Microsoft::WRL::ComPtr<ID3D11VertexShader> CreateVSShader(ID3D11Device* device, std::string fileName)
	{
		fileName = "Resources/Shaders/" + fileName;

		std::wstring wideString = std::wstring(fileName.begin(), fileName.end());
		const wchar_t* folder = wideString.c_str();

		std::vector<uint8_t> vs = DX::ReadData(folder);

		Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;

		if (FAILED(device->CreateVertexShader(vs.data(), vs.size(), NULL, vertexShader.ReleaseAndGetAddressOf())))
		{
			MessageBox(0, L"CreateVertexShader Failed", NULL, MB_OK);
		}
		return vertexShader;
	}

	/// <summary>
	/// �W�I���g���V�F�[�_�쐬
	/// </summary>
	static Microsoft::WRL::ComPtr<ID3D11GeometryShader> CreateGSShader(ID3D11Device* device, std::string fileName)
	{
		fileName = "Resources/Shaders/" + fileName;

		std::wstring wideString = std::wstring(fileName.begin(), fileName.end());
		const wchar_t* folder = wideString.c_str();

		std::vector<uint8_t> gs = DX::ReadData(folder);

		Microsoft::WRL::ComPtr<ID3D11GeometryShader> geometryShader;

		if (FAILED(device->CreateGeometryShader(gs.data(), gs.size(), NULL, geometryShader.ReleaseAndGetAddressOf())))
		{
			MessageBox(0, L"CreateGeometryShader Failed", NULL, MB_OK);
		}
		return geometryShader;
	}

	/// <summary>
	/// �s�N�Z���V�F�[�_�쐬
	/// </summary>
	static Microsoft::WRL::ComPtr<ID3D11PixelShader> CreatePSShader(ID3D11Device* device, std::string fileName)
	{
		fileName = "Resources/Shaders/" + fileName;

		std::wstring wideString = std::wstring(fileName.begin(), fileName.end());
		const wchar_t* folder = wideString.c_str();

		std::vector<uint8_t> ps = DX::ReadData(folder);

		Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;

		if (FAILED(device->CreatePixelShader(ps.data(), ps.size(), NULL, pixelShader.ReleaseAndGetAddressOf())))
		{
			MessageBox(0, L"CreatePixelShader Failed", NULL, MB_OK);
		}
		return pixelShader;
	}

	/// <summary>
	/// �萔�o�b�t�@�̍쐬
	/// </summary>
	template<typename T>
	static Microsoft::WRL::ComPtr<ID3D11Buffer> CreateConstantBuffer(ID3D11Device* device)
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(T);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		device->CreateBuffer(&bd, nullptr, &constantBuffer);

		return constantBuffer;
	}

	/// <summary>
	/// �萔�o�b�t�@�̃o�C���h
	/// </summary>
	static void BindConstantBuffer(ID3D11DeviceContext* context, ID3D11Buffer* buffer, UINT slot, ShaderType shaderType)
	{
		switch (shaderType)
		{
		case ShaderType::VertexShader:
			context->VSSetConstantBuffers(slot, 1, &buffer);
			break;
		case ShaderType::PixelShader:
			context->PSSetConstantBuffers(slot, 1, &buffer);
			break;
		case ShaderType::GeometryShader:
			context->GSSetConstantBuffers(slot, 1, &buffer);
			break;
		}
	}
	/// <summary>
	/// �C���v�b�g���C�A�E�g�쐬
	/// </summary>
	static Microsoft::WRL::ComPtr<ID3D11InputLayout> CreateInputLayout(ID3D11Device* device, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layoutDesc, std::string fileName)
	{
		fileName = "Resources/Shaders/" + fileName;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;

		std::wstring wideString = std::wstring(fileName.begin(), fileName.end());
		const wchar_t* folder = wideString.c_str();

		std::vector<uint8_t> vs = DX::ReadData(folder);

		device->CreateInputLayout(
			layoutDesc.data(),
			static_cast<UINT>(layoutDesc.size()),
			vs.data(),
			vs.size(),
			&inputLayout);

		return inputLayout;
	}

	/// <summary>
	/// �V�F�[�_�̃Z�b�g
	/// </summary>
	static void SetShaders(ID3D11DeviceContext* context, ID3D11VertexShader* vertexShader, ID3D11PixelShader* pixelShader)
	{
		context->VSSetShader(vertexShader, nullptr, 0);
		context->PSSetShader(pixelShader, nullptr, 0);
	}

	static void SetShaders(ID3D11DeviceContext* context, ID3D11VertexShader* vertexShader,
		ID3D11GeometryShader* geometryShader, ID3D11PixelShader* pixelShader)
	{
		context->VSSetShader(vertexShader, nullptr, 0);
		context->GSSetShader(geometryShader, nullptr, 0);
		context->PSSetShader(pixelShader, nullptr, 0);
	}

};
