/*
	@file	PlayScene.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "PlayScene.h"
#include <cassert>


#include "GameBase/Component/Components.h"
#include "Game/Stage/StageFactory.h"
#include "Game/Player/Player2.h"
#include "Game/Camera/PayScene/PlaySceneCamera.h"
#include "Game/Camera/PayScene/PlaySceneCamera.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/UI/PlayScene/Canvas/PlaySceneScreenSpaceOverlayCanvas.h"



//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayScene::PlayScene(SceneManager::StageID stageID)
	:
	m_camera{}
{
	//Messenger::GetInstance()->Clear();


	
	

}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayScene::~PlayScene()
{

	// do nothing.
	//Messenger::GetInstance()->Clear();



}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayScene::Initialize()
{

	using namespace DirectX::SimpleMath;

	//Messenger::GetInstance()->Rigister(GamePlayMessageType::NEXT_SCENE, this);

	//カメラの作成
	m_camera = AddActor<PlaySceneCamera>(this);
	//ステージファクトリー作成
	AddActor<StageFactory>(this);



	//プレイヤ作成	
	auto player =  AddActor<Player2>(this);
	//ボス敵の作成
	auto bossEnemy = AddActor<BossEnemy>(this);
	
	auto ui = AddActor<PlaySceneScreenSpaceOverlayCanvas>(this);

	//プレイヤの登録
	auto camera = static_cast<PlaySceneCamera*>(m_camera);
	camera->SetPlayer(player);

	player->SetPlaySceneCamera(camera);

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayScene::SceneUpdate(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayScene::SceneRender()
{
	

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayScene::Finalize()
{
	// do nothing.
}




void PlayScene::Notify(const Telegram<GamePlayMessageType>& telegram)
{

	switch (telegram.messageType)
	{
		case GamePlayMessageType::NEXT_SCENE:
		{
			auto next = static_cast<Scene::SceneID*>(telegram.extraInfo);

			SetNextSceneID(*next);
		}
			break;
		default:
			break;
	}

}
