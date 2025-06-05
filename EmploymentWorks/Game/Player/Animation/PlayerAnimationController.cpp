#include "pch.h"
#include "PlayerAnimationController.h"
#include "Game/Player/Player2.h"
#include "Game/Player/Model/PlayerModel.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player"></param>
PlayerAnimationController::PlayerAnimationController(Player2* player)
	:
	AnimationController()
{
	//パーツ情報の取得
	auto partss = player->GetPlayerModel()->GetParts();


	//名前とトランスフォームのペアの作成
	//格納変数
	std::vector<std::pair<std::string,Transform*>> data;

	for (auto& parts : partss)
	{
		//名前とトランスフォームの追加
		data.push_back(std::make_pair(parts.first,parts.second->GetTransform()));
	}
		
	


	//各Animationの作成

	


}

/// <summary>
/// デストラクタ
/// </summary>
PlayerAnimationController::~PlayerAnimationController()
{
}
