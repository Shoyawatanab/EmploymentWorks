/*
    クラス名     : StageSelectScene
    説明         : セレクトシーン
    補足・注意点 :
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include "Game/Scene/SceneManager.h"



class StageSelectScene  :  public Scene
{
public:
    //カメラの取得
	Camera* GetCamera() const override { return m_camera; };


public:
    //コンストラクタ
    StageSelectScene(SceneManager* sceneManager);
    //デストラクタ
    ~StageSelectScene() override;
    //初期化
    void Initialize() override;
    
private:
    Camera* m_camera;


};
