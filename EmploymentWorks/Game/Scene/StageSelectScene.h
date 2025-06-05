/*
	@file	StageSelectScene.h
	@brief	タイトルシーンクラス
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include "Game/Scene/SceneManager.h"
#include "Libraries/WataLib/UserInterface.h"

// 前方宣言
class CommonResources;





class StageSelectScene  :  public Scene
{
public:
	static constexpr int BUTTOM_INIAL_ID{ -1000 };


public:
    StageSelectScene(SceneManager* sceneManager);
    ~StageSelectScene() override;

	Camera* GetCamera() const { return nullptr; };




public:

    void Initialize() override;
    void SceneUpdate(float elapsedTime)override;
    void SceneRender() override;
    void Finalize() override;

	SceneID GetSceneID() const override { return SceneID::STAGESELECT; }

private:
	// 共通リソース
	CommonResources* m_commonResources;

	SceneManager* m_sceneManager;


	std::vector <std::unique_ptr<UserInterface>> m_textures;

	// シーンチェンジフラグ
	bool m_isChangeScene;

	std::unordered_map<int, std::unique_ptr<UserInterface>> m_buttom;

	int m_selectButtomId;


};
