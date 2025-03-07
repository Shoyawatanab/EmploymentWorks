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

	std::unique_ptr<WataLib::DrawTexture > m_stage1UI;
	std::unique_ptr<WataLib::DrawTexture > m_tutorialUI;

	std::unique_ptr<WataLib::DrawTexture > m_backGround;

	std::vector < std::unique_ptr<WataLib::DrawTexture>> m_textures;

	std::unique_ptr<WataLib::DrawTexture > m_arrow;

	// シーンチェンジフラグ
	bool m_isChangeScene;

};
