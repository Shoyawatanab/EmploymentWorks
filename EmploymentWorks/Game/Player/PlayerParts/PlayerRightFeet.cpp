#include "pch.h"
#include "PlayerRightFeet.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Player/PlayerPartss.h"
#include "Game/Params.h"




PlayerRightFeet::PlayerRightFeet(Scene* scene)
	:
	PlayerParts(scene, PARTS_NAME, "PlayerFeet")
{
	//�傫��
	GetTransform()->SetScale(Params::PLAYER_RIGHTFEET_SCALE);
	//�ʒu���
	GetTransform()->Translate(Params::PLAYER_RIGHTFEET_POSITION);
	//��]
	GetTransform()->SetRotate(Params::PLAYER_RIGHTFEET_ROTATION);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerRightFeet::~PlayerRightFeet()
{

}



