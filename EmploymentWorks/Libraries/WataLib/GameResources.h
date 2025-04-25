#pragma once
#include <unordered_map>


namespace FMOD
{
	class Sound;
	class System;
}



namespace WataLib
{

	class GameResources
	{
		// ------------------------
		// �t�@�C���p�X
		// ------------------------
	public:
		// ���f����Json�t�@�C��
		static const wchar_t* MODEL_JSON;
		static const wchar_t* MODEL_BASE_PATH;

		// �e�N�X�`����Json�t�@�C��
		static const wchar_t* TEXTURE_JSON;
		static const wchar_t* TEXTURE_BASE_PATH;


		// ------------------------
		// �A�N�Z�T
		// ------------------------
	public:

		// ���f�����擾����
		DirectX::Model* GetModel(std::string key) const;
		// �e�N�X�`�����擾����
		ID3D11ShaderResourceView* GetTexture(std::string key) const;

		FMOD::Sound* GetSound(std::string key) const;

		// ------------------------
		// ���J�֐�
		// ------------------------
	public:
		// �R���X�g���N�^
		GameResources(ID3D11Device1* device);
		// �f�X�g���N�^
		~GameResources() = default;

		// ------------------------
		// �����֐�
		// ------------------------
	private:
		// Json�t�@�C����ǂݍ���Ń��f���𐶐�����
		void LoadModelFromJson(ID3D11Device1* device);

		// �e�N�X�`����ǂݍ���
		void LoadTexture(ID3D11Device1* device);


		// ------------------------
		// �����ϐ�
		// ------------------------
	private:

		// ���\�[�X
		static std::unique_ptr<WataLib::GameResources> m_resources;

		// ���f�����X�g
		std::unordered_map<std::string, std::unique_ptr<DirectX::Model>> m_modelList;

		// �e�N�X�`�����X�g
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textureList;

		std::unordered_map<std::string, FMOD::Sound*> m_soundList;



	};
}