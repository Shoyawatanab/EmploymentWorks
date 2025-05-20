/*
	@file	StageObjectManager.cpp
	@brief	
*/
#include "pch.h"
#include "StageObjectManager.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include <cassert>

#include "Game/StageObject/Floor.h"
#include "Game/StageObject/Wall.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="resources"></param>
StageObjectManager::StageObjectManager(CommonResources* resources)
	:
	m_commonResources{resources}
	,m_stageObjects{}
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageObjectManager::~StageObjectManager()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
void StageObjectManager::Initialize()
{

	//�I�u�W�F�N�g�̏�����
	for (auto& TypeObjects : m_stageObjects)
	{
		for (auto& object : TypeObjects.second)
		{
			object->Initialize();
		}

	}


}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void StageObjectManager::Update(const float& elapsedTime)
{

	//�I�u�W�F�N�g�̍X�V
	for (auto& TypeObjects : m_stageObjects)
	{
		for (auto& object : TypeObjects.second)
		{
			object->Update(elapsedTime);
		}

	}


}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void StageObjectManager::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{


	//�I�u�W�F�N�g�̕`��
	for (auto& TypeObjects : m_stageObjects)
	{
		for (auto& object : TypeObjects.second)
		{
			object->Render(view, projection);
		}

	}

	
}

void StageObjectManager::Finalize()
{
	// do nothing.
}

/// <summary>
/// �����蔻��N���X�ɒǉ�
/// </summary>
/// <param name="collsionManager">�R���W�����}�l�[�W���[</param>
void StageObjectManager::AddCollision(CollisionManager* collsionManager)
{

	for (auto& TypeObjects : m_stageObjects)
	{
		for (auto& object : TypeObjects.second)
		{
			object->AddCollision(collsionManager);
		}
	}
}


//�I�u�W�F�N�g�̒ǉ�
void StageObjectManager::AddObject(std::string objectType, std::unique_ptr<CollisionEntity> object)
{

	m_stageObjects[objectType].push_back(std::move(object));

}




