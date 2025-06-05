/*
	@file	PlayScene.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include "SceneManager.h"
#include "Game/Interface/IObserver.h"

// 前方宣言
class StageObjectManager;
class Player;
class CollisionManager;
class UIManager;
class TargetMarker;
class EffectsManager;
class Sky;
class UserInterface;
class SoundManager;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}

namespace WataLib
{
	class CameraManager;
}

class PlayScene  :  public Scene ,public IObserver<GamePlayMessageType>
{
public:

	Camera* GetCamera() const  override { return m_camera; };


public:
	//コンストラクタ
	PlayScene(SceneManager::StageID stageID);
	//デストラクタ
	~PlayScene() override;




private:

	Camera* m_camera;
	


public:

	void Initialize() override;
	void SceneUpdate(float elapsedTime)override;
	void SceneRender() override;

	void Finalize() override;
	
	SceneID GetSceneID() const override { return SceneID::PLAY; }

	void SetNextSceneID(SceneID ID) { m_nextScene = ID; }

private:


	//通知時に呼び出される
	void Notify(const Telegram<GamePlayMessageType>& telegram) override;


private:


	// シーンチェンジフラグ
	bool m_isChangeScene;
	//次のシーン
	SceneID m_nextScene;



};
