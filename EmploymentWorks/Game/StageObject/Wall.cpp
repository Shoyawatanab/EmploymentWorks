/*
	@file	Wall.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Wall.h"
#include "GameBase/Component/Components.h"



Wall::Wall(Scene* scene, StageFactory::StageParameter parameter)
	:
	Actor(scene)
{
	GetTransform()->SetPosition(parameter.Position);
	GetTransform()->SetScale(parameter.Scale);
	GetTransform()->SetRotate(parameter.Rotation);


	AddComponent<ModelComponent>(this, "Wall");

}

/// <summary>
/// デストラクタ
/// </summary>
Wall::~Wall()
{
	// do nothing.
}


