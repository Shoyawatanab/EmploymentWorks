/*
	クラス名     : SceneManager
	説明         : シーンマネージャー
	補足・注意点 :
*/
#include "pch.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "StageSelectScene.h"
#include "GameBase/Screen.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>
#include "Game/Messenger/Global/GlobalMessages.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Fade/FadeManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneManager::SceneManager()
	:
	m_currentScene{}
	,m_nextSceneID{}
	,m_fadeManager{}
{

	m_fadeManager = FadeManager::GetInstance();

	GlobalMessenger::GetInstance()->Rigister(
		{
			GlobalMessageType::CHANGE_TITLE_SCENE
			,GlobalMessageType::CHANGE_SELECT_SCENE
			,GlobalMessageType::CHANGE_PLAY_SCENE
			,GlobalMessageType::CHANGE_RESULT_SCENE
		}, this
	);

}

/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager()
{
	Finalize();
}

/// <summary>
/// 初期化
/// </summary>
void SceneManager::Initialize()
{

	//初期シーン
	ChangeScene(SceneID::PLAY);



}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void SceneManager::Update(float elapsedTime)
{
	m_currentScene->Update(elapsedTime);

	// シーンを変更しないとき
	if (m_nextSceneID == SceneID::NONE) return;

	//フェード
	if (m_fadeManager->GetFadeState() != FadeManager::FadeState::NONE)
	{
		return;
	}

	//シーン切り替え
	ChangeScene(m_nextSceneID);
	//初期化
	m_nextSceneID = SceneID::NONE;
	
}

/// <summary>
/// 描画
/// </summary>
void SceneManager::Render()
{
	m_currentScene->Render();
}


/// <summary>
/// 後始末
/// </summary>
void SceneManager::Finalize()
{
	DeleteScene();
}


/// <summary>
/// シーン変更
/// </summary>
/// <param name="sceneID"></param>
void SceneManager::ChangeScene(SceneID sceneID)
{
	DeleteScene();
	CreateScene(sceneID);
}

/// <summary>
/// シーンの作成
/// </summary>
/// <param name="sceneID"></param>
void SceneManager::CreateScene(SceneID sceneID)
{
	assert(m_currentScene == nullptr);

	switch (sceneID)
	{
		case SceneID::TITLE:
			m_currentScene = std::make_unique<TitleScene>();
			break;
		case SceneID::PLAY:
			m_currentScene = std::make_unique<PlayScene>();
			break;
		case SceneID::STAGESELECT:
			m_currentScene = std::make_unique<StageSelectScene>(this);
			break;
		case SceneID::RESULT:
			m_currentScene = std::make_unique<ResultScene>();
			break;
		default:
			assert(!"SceneManager::CreateScene::シーン名が存在しません！");
			// no break
	}

	assert(m_currentScene && "SceneManager::CreateScene::次のシーンが生成されませんでした！");
	m_currentScene->Initialize();

}

/// <summary>
/// シーンの削除
/// </summary>
void SceneManager::DeleteScene()
{
	if (m_currentScene)
	{
		m_currentScene.reset();
		//メッセンジャーもクリア
		SceneMessenger::GetInstance()->Clear();

	}

}



/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void SceneManager::Notify(GlobalMessageType type, void* datas)
{
	UNREFERENCED_PARAMETER(datas);
	switch (type)
	{
		case GlobalMessageType::CHANGE_TITLE_SCENE:
			SetNextSceneID(SceneID::TITLE);
			break;
		case GlobalMessageType::CHANGE_SELECT_SCENE:
			SetNextSceneID(SceneID::STAGESELECT);
			break;
		case GlobalMessageType::CHANGE_PLAY_SCENE:
			SetNextSceneID(SceneID::PLAY);
			break;
		case GlobalMessageType::CHANGE_RESULT_SCENE:
			SetNextSceneID(SceneID::RESULT);
			break;
		default:
			break;
	}
}



