#pragma once
#include "GameBase/Model/ModelBase.h"
#include "GameBase/Scene/Scene.h"
#include <string>
#include <unordered_map>

class PlayerModel : public Actor
{
public:
	//パーツの取得
	std::unordered_map<std::string, ModelBase*>& GetParts() { return m_parts; }


public:
	//コンストラクタ
	PlayerModel(Scene* scene);
	//でストリング
	~PlayerModel();

	//パーツの登録
	void AddParts(std::vector<ModelBase*> parts);

private:

	//パーツ
	std::unordered_map<std::string, ModelBase*> m_parts;

};
