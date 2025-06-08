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
	std::vector<std::pair<std::string,Actor*>> data;

	for (auto& parts : partss)
	{
		//名前とトランスフォームの追加
		data.push_back(std::make_pair(parts.first,parts.second));
	}
		
	
	
	//各Animationの作成
	AddAnimatoin(player,"PlayerIdle","Resources/Json/PlayerData/Animation/PlayerIdle.json",data,true);
	AddAnimatoin(player,"PlayerMove","Resources/Json/PlayerData/Animation/PlayerMove.json",data);
	AddAnimatoin(player,"PlayerGetReady","Resources/Json/PlayerData/Animation/PlayerBoomerangGetReady.json",data);
	AddAnimatoin(player,"PlayerThrow","Resources/Json/PlayerData/Animation/PlayerBoomerangThrow.json",data);
	
	//遷移パラメーターの作成   状態遷移時に使用する名前
	CrateTransitionParameter({
		{"Idle",        ExecutionState::TRIIGER}
		,{"Move",      ExecutionState::FLOAT}
		,{"GetReady",   ExecutionState::TRIIGER}
		,{"Throw",      ExecutionState::TRIIGER}
		});

	//基準値スピード
	float speed = 0.1f;

	//状態遷移フローの作成　　　　　　アニメーション名　　　　　遷移名　　　遷移名に重複がないように
	CreateAnyStateToTriggerTransition("PlayerIdle",           "Idle");
	CreateAnyStateToTriggerTransition("PlayerGetReady",       "GetReady");
	CreateAnyStateToTriggerTransition("PlayerThrow",	      "Throw");
	//                    //遷移元　　　遷移先　　　　遷移名 基準値　　状態　大きいか　小さいか
	CreateFloatTransition("PlayerIdle", "PlayerMove", "Move",speed, FloatState::Greater);

	//MoveだけIdleからのアローを作成　そのほかわAnystateのフローの作成


}

/// <summary>
/// デストラクタ
/// </summary>
PlayerAnimationController::~PlayerAnimationController()
{
}
