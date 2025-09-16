/*
	クラス名     : PlaySceneWorldSpaceCanvas
	説明         : プレイシーンの3D空間のキャンバス
	補足・注意点 :
*/
#include "pch.h"
#include "PlaySceneWorldSpaceCanvas.h"
#include "GameBase/Scene/Scene.h"
#include "Game/UI/PlayScene/PlaySceneUIs.h"
#include "Game/GlobalGameData.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Component/Components.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
PlaySceneWorldSpaceCanvas::PlaySceneWorldSpaceCanvas(Scene* scene)
	:
	WorldSpaceCanvas(scene)
{

	GetScene()->AddActor<BossHp>(this);


	//ステージごとのUI
	StageUI();


}

/// <summary>
/// デストラクタ
/// </summary>
PlaySceneWorldSpaceCanvas::~PlaySceneWorldSpaceCanvas()
{



}



/// <summary>
/// ステージごとのUI
/// </summary>
void PlaySceneWorldSpaceCanvas::StageUI()
{
	//ステージ番号の取得
	int StageNumber = GlobalGameData::GetInstance()->GetSelectStateNumber();

	switch (StageNumber)
	{
		case 1:

			GetScene()->AddActor<BirdEnemyHP>(this);

			break;
		case 2:
			break;
		default:
			break;
	}


}



