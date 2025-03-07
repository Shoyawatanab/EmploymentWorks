#pragma once
/*
	@file	StageObjectManager.h.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "pch.h"
#include "Game/Entities/CollisionEntity.h"
#include <unordered_map>

// 前方宣言
class CommonResources;
class Floor;
class Wall;

class StageObjectManager 

{
public:
	StageObjectManager(CommonResources* resources);
	~StageObjectManager() ;

	void Initialize();

	//更新処理
	void  Update(const float& elapsedTime) ;


	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) ;
	void Finalize() ;

	//当たり判定クラスに登録
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
	// 共通リソース
	CommonResources* m_commonResources;


	std::unordered_map<std::string, std::vector<std::unique_ptr<CollisionEntity>>> m_stageObjects;

};
