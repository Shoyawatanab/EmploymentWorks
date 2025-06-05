#include "pch.h"
#include "PlayerModel.h"
#include "Game/Player/PlayerPartss.h"
#include "GameBase/Component/Transform/Transform.h"
#include "Game/Params.h"

PlayerModel::PlayerModel(Scene* scene)
	:
	Actor(scene)
	,m_parts{}
{

	//Bodyの作成
	auto body = GetScene()->AddActor<PlayerBody>(GetScene());
	//親の登録
	body->GetTransform()->SetParent(GetTransform());

	auto parts = body->GetAllDescendants();

	AddParts(parts);

	GetTransform()->SetScale(Params::PLAYER_SCALE);
	GetTransform()->Translate(Params::PLAYER_POSITION);
	GetTransform()->SetRotate(Params::PLAYER_ROTATION);

}

/// <summary>
/// でストリング
/// </summary>
PlayerModel::~PlayerModel()
{
	//クリア
	m_parts.clear();
}

/// <summary>
/// パーツの登録
/// </summary>
/// <param name=""></param>
void PlayerModel::AddParts(std::vector<ModelBase*> partss)
{

	for (auto& parts : partss)
	{
		//パーツ名の取得
		auto name = parts->GetPartsName();
		//登録されたパーツ名があるか
		auto sertchParts = m_parts.find(name);
		//あれば
		if (sertchParts != m_parts.end())
		{
			continue;
		}

		m_parts[name] = parts;


	}

}
