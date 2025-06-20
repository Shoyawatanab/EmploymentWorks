#include "pch.h"
#include "GameResources.h"
#include <fstream>
#include "nlohmann/json.hpp"
#include "GameBase/Common/Commons.h"
#include "Libraries/FMOD/inc/fmod.hpp"



// ���f����Json�t�@�C��
const wchar_t* GameResources::MODEL_JSON = L"Resources/Json/ModelData.json";
// ���f���̃x�[�X�p�X
const wchar_t* GameResources::MODEL_BASE_PATH = L"Resources/Models/";


// �e�N�X�`���̃x�[�X�p�X
const wchar_t* GameResources::TEXTURE_BASE_PATH = L"Resources/Textures/";
// �e�N�X�`����Json�t�@�C��
const wchar_t* GameResources::TEXTURE_JSON = L"Resources/Json/TextureData.json";




/// <summary>
/// �R���e�L�X�g
/// </summary>
/// <param name="device">�f�o�C�X</param>
GameResources::GameResources()
{
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// Json�t�@�C����ǂݍ���Ń��f���𐶐�����
	LoadModelFromJson(device);
	// �e�N�X�`����ǂݍ���
	LoadTexture(device);

}


/// <summary>
/// ���f���̓ǂݍ���
/// </summary>
/// <param name="device">�f�o�C�X</param>
void GameResources::LoadModelFromJson(ID3D11Device1* device)
{
	// Json�t�@�C�����J��
	std::ifstream ifs(MODEL_JSON);
	if (!ifs)
	{
		MessageBoxA(nullptr, "Json�t�@�C����������܂���", "�G���[", MB_OK);
		return; // �������I��
	}

	// Json�t�@�C����ǂݍ���
	nlohmann::json json = nlohmann::json::parse(ifs);

	// Json�f�[�^�����ɏ���
	for (auto it = json.begin(); it != json.end(); ++it)
	{
		// �L�[�ƒl���擾
		std::string key = it.key();
		std::string pathStr = it.value();

		// std::string��std::wstring�ɕϊ�
		std::wstring path = MODEL_BASE_PATH + std::wstring(pathStr.begin(), pathStr.end());

		// ���f���t�@�N�g���̐���
		std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
		fx->SetDirectory(L"Resources/Models");

		// ���f���𐶐�
		auto model = DirectX::Model::CreateFromCMO(device, path.c_str(), *fx);

		// ���f�������X�g�ɒǉ�
		m_modelList[key] = std::move(model);
	}

}

/// <summary>
/// �摜��ǂݍ���
/// </summary>
/// <param name="device">�f�o�C�X</param>
void GameResources::LoadTexture(ID3D11Device1* device)
{
	// Json�t�@�C�����J��
	std::ifstream ifs(TEXTURE_JSON);
	if (!ifs)
	{
		MessageBoxA(nullptr, "Json�t�@�C����������܂���", "�G���[", MB_OK);
		return; // �������I��
	}

	// Json�t�@�C����ǂݍ���
	nlohmann::json json = nlohmann::json::parse(ifs);

	// Json�f�[�^�����ɏ���
	for (auto it = json.begin(); it != json.end(); ++it)
	{
		// �L�[�ƒl���擾
		std::string key = it.key();
		std::string pathStr = it.value();

		// std::string��std::wstring�ɕϊ�
		std::wstring path = TEXTURE_BASE_PATH + std::wstring(pathStr.begin(), pathStr.end());

		// �e�N�X�`���𐶐�
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

		DirectX::CreateWICTextureFromFileEx(
			device,
			path.c_str(),
			0,
			D3D11_USAGE_DEFAULT,
			D3D11_BIND_SHADER_RESOURCE,
			0,
			0,
			DirectX::WIC_LOADER_IGNORE_SRGB,
			nullptr,
			texture.GetAddressOf()
		);
		// �e�N�X�`�������X�g�ɒǉ�
		m_textureList[key] = texture;
	}
}

/// <summary>
/// ���f���̎擾
/// </summary>
/// <param name="key">�L�[</param>
/// <returns>���f�����</returns>
DirectX::Model* GameResources::GetModel(std::string key) const
{
	// �L�[������
	auto it = m_modelList.find(key);
	if (it != m_modelList.end())
	{
		// ���f����Ԃ�
		return it->second.get();
	}
	else
	{
		// �G���[���b�Z�[�W��\��
		MessageBoxA(nullptr, "���f����������܂���", "�G���[", MB_OK);
		return nullptr;
	}
}

/// <summary>
/// �摜�̎擾
/// </summary>
/// <param name="key">�L�[</param>
/// <returns>�摜���</returns>
ID3D11ShaderResourceView* GameResources::GetTexture(std::string key) const
{
	// �L�[������
	auto it = m_textureList.find(key);

	if (it != m_textureList.end())
	{
		// �e�N�X�`����Ԃ�
		return it->second.Get();
	}
	else
	{
		// �G���[���b�Z�[�W��\��
		MessageBoxA(nullptr, "�e�N�X�`����������܂���", "�G���[", MB_OK);
		return nullptr;
	}

}



