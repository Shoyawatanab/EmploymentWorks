/*
	@file	Floor.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Floor.h"
#include "Game/Component/Components.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
/// <param name="parameter">パラメーター</param>
Floor::Floor(Scene* scene, StageFactory::StageParameter parameter)
	:
	Actor(scene)
{

	GetTransform()->SetPosition(parameter.Position);
	GetTransform()->SetScale(parameter.Scale);
	GetTransform()->SetRotate(parameter.Rotation);


	AddComponent<ModelComponent>(this, "Floor");

	AddComponent<AABB>(this, ColliderComponent::ColliderTag::AABB, CollisionType::FIXED
		,DirectX::SimpleMath::Vector3(1,1,1), 2.0f);
	
	
}

/// <summary>
/// デストラクタ
/// </summary>
Floor::~Floor()
{
}
