#include "pch.h"
#include "ShaderFactory.h"
#include "Libraries/MyLib/BinaryFile.h"


/// <summary>
/// �o�[�e�b�N�X�V�F�[�_�[�̍쐬
/// </summary>
/// <param name="device">�f�o�C�X</param>
/// <param name="fileName">�t�@�C����</param>
/// <returns>�o�[�e�b�N�X�V�F�[�_�[</returns>
Microsoft::WRL::ComPtr<ID3D11VertexShader> ShaderFactory::CreateVS(ID3D11Device* device, std::string fileName)
{
	//�t�@�C���p�X�̍쐬
	std::string filePath = "Resources/Shaders/" + fileName;
	//string��wstring�ɕϊ�
	std::wstring wfile(filePath.begin(), filePath.end());
	//const wchar_t�ɕϊ�
	const wchar_t* wfilePath = wfile.c_str();

	//�o�[�e�b�N�X�V�F�[�_�[�̃f�[�^�̓ǂݍ���
	 BinaryFile VSDatas = BinaryFile::LoadFile(wfilePath);
	//�o�[�e�b�N�X�V�F�[�_�[�̊i�[�ϐ�
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;

	//	���_�V�F�[�_�쐬
	if (FAILED(device->CreateVertexShader(VSDatas.GetData(), VSDatas.GetSize(), NULL, vertexShader.ReleaseAndGetAddressOf())))
	{//	�G���[
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return nullptr;
	}

	return vertexShader;
}


/// <summary>
/// �s�N�Z���V�F�[�_�[�̍쐬
/// </summary>
/// <param name="device">�f�o�C�X</param>
/// <param name="fileName">�t�@�C����</param>
/// <returns>�s�N�Z���V�F�[�_�[</returns>
Microsoft::WRL::ComPtr<ID3D11PixelShader> ShaderFactory::CreatePS(ID3D11Device* device, std::string fileName)
{
	//�t�@�C���p�X�̍쐬
	std::string filePath = "Resources/Shaders/" + fileName;
	//string��wstring�ɕϊ�
	std::wstring wfile(filePath.begin(), filePath.end());
	//const wchar_t�ɕϊ�
	const wchar_t* wfilePath = wfile.c_str();

	//�s�N�Z���V�F�[�_�[�̃f�[�^�̓ǂݍ���
	BinaryFile PSDatas = BinaryFile::LoadFile(wfilePath);
	//�s�N�Z���V�F�[�_�[�̊i�[�ϐ�
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;

	//	�s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(PSDatas.GetData(), PSDatas.GetSize(), NULL, pixelShader.ReleaseAndGetAddressOf())))
	{//	�G���[
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return nullptr;
	}

	return pixelShader;

}

/// <summary>
/// �W�I���g���V�F�[�_�[�̍쐬
/// </summary>
/// <param name="device">�f�o�C�X</param>
/// <param name="fileName">�t�@�C����</param>
/// <returns>�W�I���g���V�F�[�_�[</returns>
Microsoft::WRL::ComPtr<ID3D11GeometryShader> ShaderFactory::CreateGS(ID3D11Device* device, std::string fileName)
{
	//�t�@�C���p�X�̍쐬
	std::string filePath = "Resources/Shaders/" + fileName;
	//string��wstring�ɕϊ�
	std::wstring wfile(filePath.begin(), filePath.end());
	//const wchar_t�ɕϊ�
	const wchar_t* wfilePath = wfile.c_str();

	//�W�I���g���V�F�[�_�[�̃f�[�^�̓ǂݍ���
	BinaryFile GSDatas = BinaryFile::LoadFile(wfilePath);
	//�W�I���g���V�F�[�_�[�̊i�[�ϐ�
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> geometryShader;

	//	�W�I���g���V�F�[�_�쐬
	if (FAILED(device->CreateGeometryShader(GSDatas.GetData(), GSDatas.GetSize(), NULL, geometryShader.ReleaseAndGetAddressOf())))
	{//	�G���[
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return nullptr;
	}

	return geometryShader;
}

Microsoft::WRL::ComPtr<ID3D11InputLayout> ShaderFactory::CreateInputLayout(ID3D11Device* device, const std::vector<D3D11_INPUT_ELEMENT_DESC> layout, std::string fileName)
{
	

	//�t�@�C���p�X�̍쐬
	std::string filePath = "Resources/Shaders/" + fileName;
	//string��wstring�ɕϊ�
	std::wstring wfile(filePath.begin(), filePath.end());
	//const wchar_t�ɕϊ�
	const wchar_t* wfilePath = wfile.c_str();

	//�o�[�e�b�N�X�V�F�[�_�[�̃f�[�^�̓ǂݍ���
	BinaryFile VSDatas = BinaryFile::LoadFile(wfilePath);

	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;

	//�C���v�b�g���C�A�E�g�̍쐬
	device->CreateInputLayout(&layout[0],
		static_cast<UINT>(layout.size()),
		VSDatas.GetData(), VSDatas.GetSize(),
		inputLayout.GetAddressOf());

	return inputLayout;

}
