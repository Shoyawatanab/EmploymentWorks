#pragma once
#ifndef RESOURCES_DEFINED
#define RESOURCES_DEFINED
#include "Model.h"
#include "Game/CommonResources.h"

// Resources�N���X���`����
class Resources
{
public:
	// �u�v���C���v���f�����擾����
	DirectX::Model* GetPlayerModel() { return m_playerModel.get(); }
	// �u�G�v���f�����擾����
	DirectX::Model* GetEnemyModel() { return m_enemyModel.get(); }
	// �u�u�[�������v���f�����擾����
	DirectX::Model* GetBoomerangModel() { return m_boomerangModel.get(); }
	// �u���v���f�����擾����
	DirectX::Model* GetFloorModel() { return m_floorModel.get(); }
	// �u��v���f�����擾����
	DirectX::Model* GetRockModel() { return m_rockModel.get(); }
	// �u��v���f�����擾����
	DirectX::Model* GetSkyModel() { return m_skyModel.get(); }
	// �u�؂P�v���f�����擾����
	DirectX::Model* GetTree1Model() { return m_tree1Model.get(); }



public:
	Resources(Resources&&) = default;
	Resources& operator= (Resources&&) = default;
	Resources& operator= (Resources const&) = delete;
	// �f�X�g���N�^
	~Resources() = default;
	// Resouces�N���X�̃C���X�^���X���擾����
	static Resources* const GetInstance();
	// ���\�[�X�����[�h����
	void LoadResource(CommonResources* resources);

private:
	// �R���X�g���N�^
	Resources() noexcept
		:
		m_playerModel{},
		m_enemyModel{},
		m_boomerangModel{},
		m_floorModel{},
		m_rockModel{},
		m_skyModel{},
		m_tree1Model{}
	{
	}

private:
	// ���\�[�X
	static std::unique_ptr<Resources> m_resources;

	// �u�v���C���v���f��
	std::unique_ptr<DirectX::Model> m_playerModel;
	// �u�G�v���f��
	std::unique_ptr<DirectX::Model> m_enemyModel;
	// �u�u�[�������v���f��
	std::unique_ptr<DirectX::Model> m_boomerangModel;
	// �u���v���f��
	std::unique_ptr<DirectX::Model> m_floorModel;
	// �u��v���f��
	std::unique_ptr<DirectX::Model> m_rockModel;
	// �u��v���f��
	std::unique_ptr<DirectX::Model> m_skyModel;
	// �u�؂P�v���f��
	std::unique_ptr<DirectX::Model> m_tree1Model;


};

#endif		// RESOURCES_DEFINED
