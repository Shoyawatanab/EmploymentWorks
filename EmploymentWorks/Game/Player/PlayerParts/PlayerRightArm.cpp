#include "pch.h"
#include "PlayerBody.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Player/PlayerPartss.h"
#include "Game/Params.h"



/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
PlayerRightArm::PlayerRightArm(Scene* scene)
	:
	PlayerParts(scene, PARTS_NAME, "PlayerArm")
{

	//�傫��
	GetTransform()->SetScale(Params::PLAYER_RIGHTARM_SCALE);
	//�ʒu���
	GetTransform()->Translate(Params::PLAYER_RIGHTARM_POSITION);
	//��]
	GetTransform()->SetRotate(Params::PLAYER_RIGHTARM_ROTATION);


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerRightArm::~PlayerRightArm()
{
}





