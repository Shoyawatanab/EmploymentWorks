/*
	@file	Wall.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "Wall.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
/// <param name="parameter">�p�����[�^�[</param>
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
/// �f�X�g���N�^
/// </summary>
Wall::~Wall()
{
	// do nothing.
}


