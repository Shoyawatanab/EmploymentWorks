/*
	クラス名     : PlaySceneWorldSpaceCanvas
	説明         : プレイシーンの3D空間のキャンバス
	補足・注意点 :
*/
#pragma once
#include "GameBase/UI/Canvas/WorldSpaceCanvas.h"
#include "Game/Messenger/Messengers.h"


class PlaySceneWorldSpaceCanvas : public WorldSpaceCanvas
{

public:
	//コンストラクタ
	PlaySceneWorldSpaceCanvas(Scene* scene);
	//デストラクタ
	~PlaySceneWorldSpaceCanvas() override;

	//鳥的HPの作成
	void AddBirdEnemyHP(std::vector<Actor*> enemys);

private:

	//ステージごとのUI
	void StageUI();


};
