#include "pch.h"
#include "PlayerBody.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Player/PlayerPartss.h"
#include "Game/Params.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
PlayerBody::PlayerBody(Scene* scene)
	:
	PlayerParts(scene, PARTS_NAME,"PlayerBody")
{

	//�ʒu���
	GetTransform()->Translate(Params::PLAYER_BODY_POSITION);
	//�傫��
	GetTransform()->SetScale(Params::PLAYER_BODY_SCALE);
	//��]
	GetTransform()->SetRotate(Params::PLAYER_BODY_ROTATION);


	//Head�̍쐬
	auto head = GetScene()->AddActor<PlayerHead>(GetScene());
	//�e�̓o�^
	//head->GetTransform()->SetParent(GetTransform());
	head->SetParent(this);

	//LeftArm�̍쐬
	auto leftArm = GetScene()->AddActor<PlayerLeftArm>(GetScene());
	//�e�̓o�^
	//leftArm->GetTransform()->SetParent(GetTransform());
	leftArm->SetParent(this);

	//RightArm�̍쐬
	auto rightArm = GetScene()->AddActor<PlayerRightArm>(GetScene());
	//�e�̓o�^
	//rightArm->GetTransform()->SetParent(GetTransform());
	rightArm->SetParent(this);


	//LeftFeet�̍쐬
	auto leftfeet = GetScene()->AddActor<PlayerLeftFeet>(GetScene());
	//�e�̓o�^
	//leftfeet->GetTransform()->SetParent(GetTransform());
	leftfeet->SetParent(this);


	//rightFeet�̍쐬
	auto rightfeet = GetScene()->AddActor<PlayerRightFeet>(GetScene());
	//�e�̓o�^
	//rightfeet->GetTransform()->SetParent(GetTransform());
	rightfeet->SetParent(this);



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerBody::~PlayerBody()
{
}



