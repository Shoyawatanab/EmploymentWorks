#include "pch.h"
#include "PlayerLeftFeet.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Player/PlayerPartss.h"
#include "Game/Params.h"




PlayerLeftFeet::PlayerLeftFeet(Scene* scene)
	:
	PlayerParts(scene, PARTS_NAME, "PlayerFeet")

{

	//�傫��
	GetTransform()->SetScale(Params::PLAYER_LEFRFEET_SCALE);
	//�ʒu���
	GetTransform()->Translate(Params::PLAYER_LEFRFEET_POSITION);
	//��]
	GetTransform()->SetRotate(Params::PLAYER_LEFRFEET_ROTATION);


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerLeftFeet::~PlayerLeftFeet()
{
}



