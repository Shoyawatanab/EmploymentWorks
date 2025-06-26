#include "pch.h"
#include "PlayerLeftArm.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Player/PlayerPartss.h"
#include "Game/Params.h"




/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
PlayerLeftArm::PlayerLeftArm(Scene* scene)
	:
	PlayerParts(scene, PARTS_NAME, "PlayerArm")
{

	//�傫��
	GetTransform()->SetScale(Params::PLAYER_LEFRARM_SCALE);
	//�ʒu���
	GetTransform()->Translate(Params::PLAYER_LEFRARM_POSITION);
	//��]
	GetTransform()->SetRotate(Params::PLAYER_LEFRARM_ROTATION);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerLeftArm::~PlayerLeftArm()
{
}


