/*
	@file	Floor.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Floor.h"
#include "GameBase/Component/Components.h"

Floor::Floor(Scene* scene, StageFactory::StageParameter parameter)
	:
	Actor(scene)
{

	GetTransform()->SetPosition(parameter.Position);
	GetTransform()->SetScale(parameter.Scale);
	GetTransform()->SetRotate(parameter.Rotation);


	AddComponent<ModelComponent>(this, "Floor");

	AddComponent<AABB>(this, ColliderComponent::ColliderTag::AABB, CollisionType::FIXED
		,GetTransform()->GetScale(),  60.0f);
	
	
}

Floor::~Floor()
{
}
