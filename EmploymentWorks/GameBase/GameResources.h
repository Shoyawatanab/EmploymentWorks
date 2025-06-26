#pragma once
#include <unordered_map>

#include "Libraries/WataLib/Singleton.h"



namespace FMOD
{
	class Sound;
	class System;
}


class GameResources : public Singleton<GameResources>
{
	friend class Singleton<GameResources>;
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

public:

	// ���f�����擾����
	DirectX::Model* GetModel(std::string key) const;
	// �e�N�X�`�����擾����
	ID3D11ShaderResourceView* GetTexture(std::string key) const;

public:
	// �R���X�g���N�^
	GameResources();
	// �f�X�g���N�^
	~GameResources() = default;

private:
	// Json�t�@�C����ǂݍ���Ń��f���𐶐�����
	void LoadModelFromJson(ID3D11Device1* device);

	// �e�N�X�`����ǂݍ���
	void LoadTexture(ID3D11Device1* device);



private:


	// ���f�����X�g
	std::unordered_map<std::string, std::unique_ptr<DirectX::Model>> m_modelList;

	// �e�N�X�`�����X�g
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textureList;

	std::unordered_map<std::string, FMOD::Sound*> m_soundList;

};




