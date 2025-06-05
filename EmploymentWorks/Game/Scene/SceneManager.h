/*
	@file	SceneManager.h
	@brief	�V�[���}�l�[�W���N���X
*/
#pragma once
#include "GameBase/Scene/Scene.h"

// �O���錾
class CommonResources;

class SceneManager
{
public:
	enum StageID
	{
		STAGE1 = 0,
		STAGE2

	};

public:
	void  SetStageID(StageID stageID) { m_stageID = stageID; }



public:
	SceneManager();
	~SceneManager();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();
	void Finalize();



private:
	void ChangeScene(Scene::SceneID sceneID);
	void CreateScene(Scene::SceneID sceneID);
	void DeleteScene();

private:
	std::unique_ptr<Scene> m_currentScene;
	CommonResources* m_commonResources;

	StageID m_stageID;

};
