/*
	@file	Wall.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "Wall.h"
#include "Game/Component/Components.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
/// <param name="parameter">�p�����[�^�[</param>
Wall::Wall(Scene* scene, StageFactory::StageParameter parameter)
	:
	Actor(scene)
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetPosition(parameter.Position);
	GetTransform()->SetScale(parameter.Scale);
	GetTransform()->SetRotate(parameter.Rotation);


	AddComponent<ModelComponent>(this, "Wall");

	auto extens = Vector3::Transform(Vector3(1,0.01f,1), parameter.Rotation);
	extens.x = std::abs(extens.x);
	extens.y = std::abs(extens.y);
	extens.z = std::abs(extens.z);

	AddComponent<AABB>(this, ColliderComponent::ColliderTag::AABB, CollisionType::FIXED
		, extens, 1.5f);


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Wall::~Wall()
{
	// do nothing.
}


