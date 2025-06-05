#include "pch.h"
#include "PlayerParts.h"
#include "GameBase/Component/Components.h"



PlayerParts::PlayerParts(Scene* scene, std::string partsName, std::string modelName)
	:
	ModelBase(scene,partsName,modelName)
{



}

/// <summary>
/// デストラクタ
/// </summary>
PlayerParts::~PlayerParts()
{
}
