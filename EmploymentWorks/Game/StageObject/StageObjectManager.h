#pragma once
/*
	@file	StageObjectManager.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"
#include "Game/Entities/CollisionEntity.h"
#include <unordered_map>

// �O���錾
class CommonResources;
class Floor;
class Wall;

class StageObjectManager 

{
public:
	StageObjectManager(CommonResources* resources);
	~StageObjectManager() ;

	void Initialize();

	//�X�V����
	void  Update(const float& elapsedTime) ;


	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) ;
	void Finalize() ;

	//�����蔻��N���X�ɓo�^
	void  AddCollision(CollisionManager* collsionManager);



	std::vector<std::unique_ptr<CollisionEntity>>* GetStageObjects(const std::string objectType) 
	{
		auto it = m_stageObjects.find(objectType);
		if (it != m_stageObjects.end()) 
		{
			return &(it->second);
		}

		return nullptr;
	}


	void AddObject(std::string objectType, std::unique_ptr<CollisionEntity> object);

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;


	std::unordered_map<std::string, std::vector<std::unique_ptr<CollisionEntity>>> m_stageObjects;

};
