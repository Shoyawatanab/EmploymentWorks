/*
	@file	ResultScene.h
	@brief	タイトルシーンクラス
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include "Game/Scene/SceneManager.h"

// 前方宣言
class CommonResources;





class ResultScene  :  public Scene
{

public:
    ResultScene();
    ~ResultScene() override;

    Camera* GetCamera() const { return nullptr; };




public:


    void Initialize() override;
    void SceneUpdate(float elapsedTime)override;
    void SceneRender() override;
    void Finalize() override;

	SceneID GetSceneID() const override { return SceneID::RESULT; }
private:


	// シーンチェンジフラグ
	bool m_isChangeScene;

};
