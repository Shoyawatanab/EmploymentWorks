#pragma once
/*
	@file	Wall.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Stage/StageFactory.h"



class Wall : public Actor
{
public:
	//�I�u�W�F�N�g�^�O�̎擾
	ObjectTag GetObjectTag() override { return ObjectTag::STAGE; }

public:
	//�R���X�g���N�^
	Wall(Scene* scene, StageFactory::StageParameter parameter);

	//�f�X�g���N�^
	~Wall() override;


};
