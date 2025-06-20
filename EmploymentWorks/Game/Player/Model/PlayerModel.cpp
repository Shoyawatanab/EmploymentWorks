#include "pch.h"
#include "PlayerModel.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Player/PlayerPartss.h"
#include "GameBase/Component/Transform/Transform.h"
#include "Game/Params.h"

PlayerModel::PlayerModel(Scene* scene)
	:
	ModelBase(scene)
{

	//Bodyの作成
	auto body = GetScene()->AddActor<PlayerBody>(GetScene());
	//親の登録
	body->GetTransform()->SetParent(GetTransform());
	//子孫モデルを取得
	auto parts = body->GetAllDescendants();
	//子孫モデルをパーツに登録
	AddParts(parts);


}

/// <summary>
/// でストリング
/// </summary>
PlayerModel::~PlayerModel()
{
}


