#pragma once
/*
	@file	Floor.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Stage/StageFactory.h"

class Floor : public Actor
{
public:
	//�I�u�W�F�N�g�^�O�̎擾
	ObjectTag GetObjectTag() override { return ObjectTag::STAGE; }


public:
	//�R���X�g���N�^
	Floor(Scene* scene, StageFactory::StageParameter parameter );

	//�f�X�g���N�^
	~Floor() override;



};
