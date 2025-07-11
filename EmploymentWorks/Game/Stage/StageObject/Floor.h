#pragma once
/*
	@file	Floor.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
/*
	�N���X��     : Floor
	����         : ��
	�⑫�E���ӓ_ :
*/
#include "GameBase/Actor.h"
#include "Game/Stage/StageFactory.h"

class Floor : public Actor
{
public:

	//�����蔻��̑傫��
	static constexpr DirectX::SimpleMath::Vector3 BOX_COLLIDER_SIZE = {1.0f,1.0f,1.0f};
	static constexpr float SPHERE_COLLIDER_SIZE = 2.0f;

public:
	//�I�u�W�F�N�g�^�O�̎擾
	ObjectTag GetObjectTag() override { return ObjectTag::STAGE; }


public:
	//�R���X�g���N�^
	Floor(Scene* scene, StageFactory::StageParameter parameter );

	//�f�X�g���N�^
	~Floor() override;



};
