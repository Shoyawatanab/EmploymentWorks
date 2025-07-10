/*
	@file	Floor.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "Floor.h"
#include "Game/Component/Components.h"

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

	//���f���R���|�[�l���g�̒ǉ�
	AddComponent<ModelComponent>(this, "Floor");
	//�����蔻��R���|�[�l���g�̒ǉ��@AABB
	AddComponent<AABB>(this, CollisionType::FIXED
		,BOX_COLLIDER_SIZE, SPHERE_COLLIDER_SIZE);
	
	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Floor::~Floor()
{
}
