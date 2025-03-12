/*
	@file	StageSelectScene.h
	@brief	タイトルシーンクラス
*/
#pragma once
#include "IScene.h"
#include "Game/Scene/SceneManager.h"

// 前方宣言
class CommonResources;

namespace WataLib
{
	class DrawTexture;
}



class StageSelectScene final :
    public IScene
{
public:
	static constexpr int BUTTOM_INIAL_ID{ -1000 };


public:
    StageSelectScene(SceneManager* sceneManager);
    ~StageSelectScene() override;

    void Initialize(CommonResources* resources) override;
    void Update(float elapsedTime)override;
    void Render() override;
    void Finalize() override;

    SceneID GetNextSceneID() const;

private:
	// 共通リソース
	CommonResources* m_commonResources;

	SceneManager* m_sceneManager;


	std::vector <std::unique_ptr<WataLib::DrawTexture>> m_textures;

	// シーンチェンジフラグ
	bool m_isChangeScene;

	std::unordered_map<int, std::unique_ptr<WataLib::DrawTexture>> m_buttom;

	int m_selectButtomId;


};
