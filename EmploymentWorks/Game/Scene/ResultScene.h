/*
	@file	ResultScene.h
	@brief	タイトルシーンクラス
*/
#pragma once
#include "IScene.h"
#include "Game/Scene/SceneManager.h"

// 前方宣言
class CommonResources;





class ResultScene final :
    public IScene
{

public:
    ResultScene();
    ~ResultScene() override;

    void Initialize(CommonResources* resources) override;
    void Update(float elapsedTime)override;
    void Render() override;
    void Finalize() override;

    SceneID GetNextSceneID() const;

private:
	// 共通リソース
	CommonResources* m_commonResources;


	// シーンチェンジフラグ
	bool m_isChangeScene;

};
