/*
	@file	Floor.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "Floor.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
/// <param name="parameter">�p�����[�^�[</param>
Floor::Floor(Scene* scene, StageFactory::StageParameter parameter)
	:
	Actor(scene)
{

	GetTransform()->SetPosition(parameter.Position);
	GetTransform()->SetScale(parameter.Scale);
	GetTransform()->SetRotate(parameter.Rotation);


	AddComponent<ModelComponent>(this, "Floor");

	AddComponent<AABB>(this, ColliderComponent::ColliderTag::AABB, CollisionType::FIXED
		,GetTransform()->GetScale() + DirectX::SimpleMath::Vector3(0,0,0), 60.0f);
	
	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Floor::~Floor()
{
}
